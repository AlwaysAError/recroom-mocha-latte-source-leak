#pragma once

ImVec4 InterpolateLineColor(const ImVec4& color1, const ImVec4& color2, float t)
{
	return ImVec4(
		color1.x + t * (color2.x - color1.x),
		color1.y + t * (color2.y - color1.y),
		color1.z + t * (color2.z - color1.z),
		color1.w + t * (color2.w - color1.w)
	);
}

ImVec4 calculateColorBasedOnDistance(const Vector3& point, const Vector3& referencePoint, float minDistance, float maxDistance, const ImVec4& closeDistanceColor, const ImVec4& farDistanceColor) {
	float distance = point.distanceTo(referencePoint);
	float factor = std::clamp((distance - minDistance) / (maxDistance - minDistance), 0.0f, 1.0f);

	return ImVec4(
		closeDistanceColor.x + factor * (farDistanceColor.x - closeDistanceColor.x),
		closeDistanceColor.y + factor * (farDistanceColor.y - closeDistanceColor.y),
		closeDistanceColor.z + factor * (farDistanceColor.z - closeDistanceColor.z),
		closeDistanceColor.w + factor * (farDistanceColor.w - closeDistanceColor.w)
	);
}

ImVec4 calculateFadeBasedOnDistance(const Vector3& point, const Vector3& referencePoint, float fadeStartDistance, const ImVec4& color) {
	float distance = point.distanceTo(referencePoint);
	float factor = std::clamp((fadeStartDistance - distance) / fadeStartDistance, 0.0f, 1.0f);

	return ImVec4(
		color.x,
		color.y,
		color.z,
		color.w * (1.0f - factor) // Fade out as the point gets closer
	);
}

// Function to convert HSV to ImVec4 (RGBA)
ImVec4 HSVtoImVec4(float h, float s, float v) {
	float c = v * s;
	float x = c * (1 - fabs(fmodf(h * 6, 2) - 1));
	float m = v - c;

	float r, g, b;
	if (h < 1.0f / 6.0f) { r = c; g = x; b = 0; }
	else if (h < 2.0f / 6.0f) { r = x; g = c; b = 0; }
	else if (h < 3.0f / 6.0f) { r = 0; g = c; b = x; }
	else if (h < 4.0f / 6.0f) { r = 0; g = x; b = c; }
	else if (h < 5.0f / 6.0f) { r = x; g = 0; b = c; }
	else { r = c; g = 0; b = x; }

	return ImVec4(r + m, g + m, b + m, 1.0f);
}

// Function to get the rainbow color
ImVec4 GetRainbowColor(float factor) {
	float hue = fmodf(factor, 1.0f); // Wrap hue around
	return HSVtoImVec4(hue, 1.0f, 1.0f); // Full saturation and value for vibrant colors
}

void esp() {
	if (globals::ESP::toggle)
	{
		ThreadFix();

		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGuiIO& io = ImGui::GetIO();
		ImGui::SetNextWindowSize(io.DisplaySize);
		ImGui::Begin("ESP Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);

		auto draw = ImGui::GetWindowDrawList();

		auto bone_esp_color = ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		float screenHeight = io.DisplaySize.y;
		float screenWidth = io.DisplaySize.x;

		Vector3 localPosition{ 0, 0, 0 };

		if (localPlayer.loadingStage >= LoadingStage::LOADED) {
			RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(localPlayer.photonActorID);

			if (playerPlayer != nullptr) {

				if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {
					localPosition = playerPlayer->get_CurrentBodyPosition();
				}
			}
		}

		for (const auto& [photonPlayer, player] : cachedPlayerlist) {
			if (player.loadingStage >= LoadingStage::LOADED) {

				RecRoomPlayer* playerPlayer = RecRoomPlayer::GetFromActorNumber(player.photonActorID);

				if (playerPlayer != nullptr) {

					if (playerPlayer->get_IsInitialized() && playerPlayer->get_IsInitialLoadFinished()) {

						Camera* camera = Camera::get_current();

						Vector3 rightHandPos = playerPlayer->get_RightHand()->get_transform()->get_position();
						Vector3 leftHandPos = playerPlayer->get_LeftHand()->get_transform()->get_position();
						Vector3 headPos = playerPlayer->get_CurrentHeadPosition();
						Vector3 bodyPos = playerPlayer->get_CurrentBodyPosition();

						Vector2 w2sRight = camera->WorldToScreenPoint(rightHandPos);
						Vector2 w2sLeft = camera->WorldToScreenPoint(leftHandPos);
						Vector2 w2sHead = camera->WorldToScreenPoint(headPos);
						Vector2 w2sBody = camera->WorldToScreenPoint(bodyPos);

						Vector3 cameraPosition = camera->get_gameObject()->get_transform()->get_position();
						Vector3 directionToPlayer = headPos - cameraPosition;

						float angleToPlayer = Vector3::angle(camera->get_gameObject()->get_transform()->get_forward(), directionToPlayer);
						float playerFOV = camera->get_fieldOfView();

						if ((angleToPlayer + 10) < playerFOV) {
							LineConfig skeletonConfig = globals::ESP::skeleton;
							BoxConfig nametagOutlineConfig = globals::ESP::nametagOutline;
							BoxConfig boxOutlineConfig = globals::ESP::boxOutline;
							BoxConfig boxConfig = globals::ESP::box;
							LineConfig tracerConfig = globals::ESP::tracer;
							NametagConfig nametagConfig = globals::ESP::nametag;

							// calculate position factor based on screen position
							float positionFactorRightHand = (w2sRight.x / screenWidth) * (w2sRight.y / screenHeight);
							float positionFactorLeftHand = (w2sLeft.x / screenWidth) * (w2sLeft.y / screenHeight);
							float positionFactorBody = (w2sBody.x / screenWidth) * (w2sBody.y / screenHeight);

							// combine factors / 2.0f to average the factors

							if (skeletonConfig.state && ((player.isLocalPlayer && skeletonConfig.renderSelf) || !player.isLocalPlayer)) {

								float time = ImGui::GetTime() * skeletonConfig.gradientSpeed; // we should have different var for box but im lazy
								float gradientFactor = fmodf(time, 2.0f);

								if (gradientFactor > 1.0f)
									gradientFactor = 2.0f - gradientFactor;

								float combinedFactorRightHand = (gradientFactor + positionFactorRightHand) / 2.0f;
								float combinedFactorLeftHand = (gradientFactor + positionFactorLeftHand) / 2.0f;
								float combinedFactorBody = (gradientFactor + positionFactorBody) / 2.0f;

								auto skeletonStartColor = skeletonConfig.gradientColor ? skeletonConfig.gradientStartColor : skeletonConfig.staticColor;
								auto skeletonEndColor = skeletonConfig.gradientColor ? skeletonConfig.gradientEndColor : skeletonConfig.staticColor;

								/// normal interpolation 
								/// pointless calc here but im too lazy to optimize this
								auto interpolatedColorRightHand = skeletonConfig.rainbowColor ? GetRainbowColor(combinedFactorRightHand) : InterpolateLineColor(skeletonStartColor, skeletonEndColor, combinedFactorRightHand);
								auto interpolatedColorLeftHand = skeletonConfig.rainbowColor ? GetRainbowColor(combinedFactorLeftHand) : InterpolateLineColor(skeletonStartColor, skeletonEndColor, combinedFactorLeftHand);
								auto interpolatedColorBody = skeletonConfig.rainbowColor ? GetRainbowColor(combinedFactorBody) : InterpolateLineColor(skeletonStartColor, skeletonEndColor, combinedFactorBody);

								// calculateColorBasedOnDistance

								auto chosenColorRightHand = skeletonConfig.distanceColor ? 
									calculateColorBasedOnDistance(
									rightHandPos, 
									localPosition, 
									skeletonConfig.minDistance, 
									skeletonConfig.maxDistance, 
									skeletonConfig.closeDistanceColor, 
									skeletonConfig.farDistanceColor) : interpolatedColorRightHand;

								auto chosenColorLeftHand = skeletonConfig.distanceColor ?
									calculateColorBasedOnDistance(
										leftHandPos,
										localPosition,
										skeletonConfig.minDistance,
										skeletonConfig.maxDistance,
										skeletonConfig.closeDistanceColor,
										skeletonConfig.farDistanceColor) : interpolatedColorLeftHand;

								auto chosenColorBody = skeletonConfig.distanceColor ?
									calculateColorBasedOnDistance(
										bodyPos,
										localPosition,
										skeletonConfig.minDistance,
										skeletonConfig.maxDistance,
										skeletonConfig.closeDistanceColor,
										skeletonConfig.farDistanceColor) : interpolatedColorBody;

								/// render skeleton

								if (skeletonConfig.fade) {
									chosenColorRightHand = calculateFadeBasedOnDistance(rightHandPos, localPosition, skeletonConfig.fadeDistance, chosenColorRightHand);
									chosenColorLeftHand = calculateFadeBasedOnDistance(leftHandPos, localPosition, skeletonConfig.fadeDistance, chosenColorLeftHand);
									chosenColorBody = calculateFadeBasedOnDistance(bodyPos, localPosition, skeletonConfig.fadeDistance, chosenColorBody);
								}

								// Body -> Head
								draw->AddLine(ImVec2(w2sBody.x, screenHeight - w2sBody.y),
									ImVec2(w2sHead.x, screenHeight - w2sHead.y),
									ImGui::ColorConvertFloat4ToU32(chosenColorRightHand), skeletonConfig.lineThickness);

								// Body -> Left Hand
								draw->AddLine(ImVec2(w2sBody.x, screenHeight - w2sBody.y),
									ImVec2(w2sLeft.x, screenHeight - w2sLeft.y),
									ImGui::ColorConvertFloat4ToU32(chosenColorLeftHand), skeletonConfig.lineThickness);

								// Body -> Right Hand
								draw->AddLine(ImVec2(w2sBody.x, screenHeight - w2sBody.y),
									ImVec2(w2sRight.x, screenHeight - w2sRight.y),
									ImGui::ColorConvertFloat4ToU32(chosenColorBody), skeletonConfig.lineThickness);
							}

							/// render box

							ImVec2 padding = boxConfig.padding;

							if (boxConfig.state && ((player.isLocalPlayer && boxConfig.renderSelf) || !player.isLocalPlayer)) {

								float time = ImGui::GetTime() * boxConfig.gradientSpeed;
								float gradientFactor = fmodf(time, 2.0f);

								if (gradientFactor > 1.0f)
									gradientFactor = 2.0f - gradientFactor;

								ImVec2 min {0, 0};
								ImVec2 max {0, 0};

								if (boxConfig.dynamic) {
									float minX = w2sBody.x;
									float minY = screenHeight - w2sBody.y;
									float maxX = w2sBody.x;
									float maxY = screenHeight - w2sBody.y;

									if (w2sHead.x < minX) minX = w2sHead.x;
									if (w2sHead.x > maxX) maxX = w2sHead.x;
									if (screenHeight - w2sHead.y < minY) minY = screenHeight - w2sHead.y;
									if (screenHeight - w2sHead.y > maxY) maxY = screenHeight - w2sHead.y;

									if (w2sLeft.x < minX) minX = w2sLeft.x;
									if (w2sLeft.x > maxX) maxX = w2sLeft.x;
									if (screenHeight - w2sLeft.y < minY) minY = screenHeight - w2sLeft.y;
									if (screenHeight - w2sLeft.y > maxY) maxY = screenHeight - w2sLeft.y;

									if (w2sRight.x < minX) minX = w2sRight.x;
									if (w2sRight.x > maxX) maxX = w2sRight.x;
									if (screenHeight - w2sRight.y < minY) minY = screenHeight - w2sRight.y;
									if (screenHeight - w2sRight.y > maxY) maxY = screenHeight - w2sRight.y;

									min = ImVec2(minX - padding.x, minY - padding.y);
									max = ImVec2(maxX + padding.x, maxY + padding.y);
								}
								else {
									float minX = w2sBody.x;
									float minY = screenHeight - w2sBody.y;
									float maxX = w2sBody.x;
									float maxY = screenHeight - w2sBody.y;

									if (w2sHead.x < minX) minX = w2sHead.x;
									if (w2sHead.x > maxX) maxX = w2sHead.x;
									if (screenHeight - w2sHead.y < minY) minY = screenHeight - w2sHead.y;
									if (screenHeight - w2sHead.y > maxY) maxY = screenHeight - w2sHead.y;

									min = ImVec2(minX - padding.x, minY - padding.y);
									max = ImVec2(maxX + padding.x, maxY + padding.y);
								}

								// distance color cuz im lazy and i render it in static one smd
								bool boxStaticColor = (boxConfig.simpleGradient && boxConfig.gradientColor || boxConfig.distanceColor) ? true : false;

								if (boxStaticColor) {

									float combinedFactorBody = (gradientFactor + positionFactorBody) / 2.0f;

									auto interpolatedBoxColor = boxConfig.rainbowColor ? GetRainbowColor(combinedFactorBody) : 
										InterpolateLineColor(boxConfig.gradientStartColor, boxConfig.gradientEndColor, combinedFactorBody);

									if (boxOutlineConfig.state) { // this code is shit, suck ya mum
										/// handle outline with color and shit

										bool boxOutlineStaticColor = (!boxOutlineConfig.gradientColor && !boxOutlineConfig.distanceColor) ? true : false;

										auto interpolatedBoxOutlineColor = boxOutlineConfig.rainbowColor ? GetRainbowColor(combinedFactorBody) :
											InterpolateLineColor(boxOutlineConfig.gradientStartColor, boxOutlineConfig.gradientEndColor, combinedFactorBody);

										auto chosenInterpolatedBoxOutlineColor = boxOutlineConfig.distanceColor ? calculateColorBasedOnDistance(
											bodyPos,
											localPosition,
											boxOutlineConfig.minDistance,
											boxOutlineConfig.maxDistance,
											boxOutlineConfig.closeDistanceColor,
											boxOutlineConfig.farDistanceColor) : interpolatedBoxOutlineColor;

										auto chosenBoxOutlineColor = boxOutlineStaticColor ? boxOutlineConfig.staticColor : chosenInterpolatedBoxOutlineColor;



										if (boxOutlineConfig.fade) {
											chosenBoxOutlineColor = calculateFadeBasedOnDistance(bodyPos, localPosition, boxOutlineConfig.fadeDistance, chosenBoxOutlineColor);
										}

										draw->AddRect(
											ImVec2(min + ImVec2(1, 1)),
											ImVec2(max - ImVec2(1, 1)),
											ImGui::ColorConvertFloat4ToU32(chosenBoxOutlineColor),
											boxConfig.rounding, 0, boxOutlineConfig.lineThickness);

										draw->AddRect(
											ImVec2(min - ImVec2(1, 1)),
											ImVec2(max + ImVec2(1, 1)),
											ImGui::ColorConvertFloat4ToU32(chosenBoxOutlineColor),
											boxConfig.rounding, 0, boxOutlineConfig.lineThickness);

									}

									auto chosenInterpolatedBoxColor = boxConfig.distanceColor ?
										calculateColorBasedOnDistance(
											bodyPos,
											localPosition,
											boxConfig.minDistance,
											boxConfig.maxDistance,
											boxConfig.closeDistanceColor,
											boxConfig.farDistanceColor) : interpolatedBoxColor;

									auto chosenBoxColor = (!boxConfig.gradientColor && !boxConfig.distanceColor) ? boxConfig.staticColor : chosenInterpolatedBoxColor;
									
									if (boxConfig.fade) {
										chosenBoxColor = calculateFadeBasedOnDistance(bodyPos, localPosition, boxConfig.fadeDistance, chosenBoxColor);
									}

									// Main rectangle
									draw->AddRect(min, max, ImGui::ColorConvertFloat4ToU32(chosenBoxColor), boxConfig.rounding, 0, boxConfig.lineThickness);
								}
								else if (boxConfig.gradientColor) {
									float topLeftFactor = (gradientFactor + (min.x / screenWidth) * (min.y / screenHeight)) / 2.0f;
									float topRightFactor = (gradientFactor + (max.x / screenWidth) * (min.y / screenHeight)) / 2.0f;
									float bottomLeftFactor = (gradientFactor + (min.x / screenWidth) * (max.y / screenHeight)) / 2.0f;
									float bottomRightFactor = (gradientFactor + (max.x / screenWidth) * (max.y / screenHeight)) / 2.0f;


									auto interpolatedBoxColorTopLeft = boxConfig.rainbowColor ? ImGui::ColorConvertFloat4ToU32(GetRainbowColor(topLeftFactor)) :
										ImGui::ColorConvertFloat4ToU32(InterpolateLineColor(boxConfig.gradientStartColor, boxConfig.gradientEndColor, topLeftFactor));

									auto interpolatedBoxColorTopRight = boxConfig.rainbowColor ? ImGui::ColorConvertFloat4ToU32(GetRainbowColor(topRightFactor)) :
										ImGui::ColorConvertFloat4ToU32(InterpolateLineColor(boxConfig.gradientStartColor, boxConfig.gradientEndColor, topRightFactor));

									auto interpolatedBoxColorBottomLeft = boxConfig.rainbowColor ? ImGui::ColorConvertFloat4ToU32(GetRainbowColor(bottomLeftFactor)) :
										ImGui::ColorConvertFloat4ToU32(InterpolateLineColor(boxConfig.gradientStartColor, boxConfig.gradientEndColor, bottomLeftFactor));

									auto interpolatedBoxColorBottomRight = boxConfig.rainbowColor ? ImGui::ColorConvertFloat4ToU32(GetRainbowColor(bottomRightFactor)) :
										ImGui::ColorConvertFloat4ToU32(InterpolateLineColor(boxConfig.gradientStartColor, boxConfig.gradientEndColor, bottomRightFactor));

									if (boxConfig.fade) {
										interpolatedBoxColorTopLeft = ImGui::ColorConvertFloat4ToU32(calculateFadeBasedOnDistance(bodyPos, localPosition, boxConfig.fadeDistance, ImGui::ColorConvertU32ToFloat4(interpolatedBoxColorTopLeft)));
										interpolatedBoxColorTopRight = ImGui::ColorConvertFloat4ToU32(calculateFadeBasedOnDistance(bodyPos, localPosition, boxConfig.fadeDistance, ImGui::ColorConvertU32ToFloat4(interpolatedBoxColorTopRight)));
										interpolatedBoxColorBottomLeft = ImGui::ColorConvertFloat4ToU32(calculateFadeBasedOnDistance(bodyPos, localPosition, boxConfig.fadeDistance, ImGui::ColorConvertU32ToFloat4(interpolatedBoxColorBottomLeft)));
										interpolatedBoxColorBottomRight = ImGui::ColorConvertFloat4ToU32(calculateFadeBasedOnDistance(bodyPos, localPosition, boxConfig.fadeDistance, ImGui::ColorConvertU32ToFloat4(interpolatedBoxColorBottomRight)));
									}

									// Top rectangle
									draw->AddRectFilledMultiColor(
										ImVec2(min.x, min.y),
										ImVec2(max.x, min.y + boxConfig.lineThickness),
										interpolatedBoxColorTopLeft, interpolatedBoxColorTopRight,
										interpolatedBoxColorTopRight, interpolatedBoxColorTopLeft
									);

									// Bottom rectangle
									draw->AddRectFilledMultiColor(
										ImVec2(min.x, max.y - boxConfig.lineThickness),
										ImVec2(max.x, max.y),
										interpolatedBoxColorBottomLeft, interpolatedBoxColorBottomRight,
										interpolatedBoxColorBottomRight, interpolatedBoxColorBottomLeft
									);

									// Left rectangle
									draw->AddRectFilledMultiColor(
										ImVec2(min.x, min.y),
										ImVec2(min.x + boxConfig.lineThickness, max.y),
										interpolatedBoxColorTopLeft, interpolatedBoxColorBottomLeft,
										interpolatedBoxColorBottomLeft, interpolatedBoxColorTopLeft
									);

									// Right rectangle
									draw->AddRectFilledMultiColor(
										ImVec2(max.x - boxConfig.lineThickness, min.y),
										ImVec2(max.x, max.y),
										interpolatedBoxColorTopRight, interpolatedBoxColorBottomRight,
										interpolatedBoxColorBottomRight, interpolatedBoxColorTopRight
									);


									/// outline shit goes here

									if (boxOutlineConfig.state) {

										ImVec2 outlineMin = ImVec2(min.x - boxOutlineConfig.lineThickness, min.y - boxOutlineConfig.lineThickness);
										ImVec2 outlineMax = ImVec2(max.x + boxOutlineConfig.lineThickness, max.y + boxOutlineConfig.lineThickness);

										// Calculate factors for the corners using outline coordinates
										float outlineTopLeftFactor = (gradientFactor + (outlineMin.x / screenWidth) * (outlineMin.y / screenHeight)) / 2.0f;
										float outlineTopRightFactor = (gradientFactor + (outlineMax.x / screenWidth) * (outlineMin.y / screenHeight)) / 2.0f;
										float outlineBottomLeftFactor = (gradientFactor + (outlineMin.x / screenWidth) * (outlineMax.y / screenHeight)) / 2.0f;
										float outlineBottomRightFactor = (gradientFactor + (outlineMax.x / screenWidth) * (outlineMax.y / screenHeight)) / 2.0f;


										bool boxOutlineStaticColor = (!boxOutlineConfig.gradientColor && !boxOutlineConfig.distanceColor) ? true : false;


										auto interpolatedBoxOutlineColorTopLeft = boxOutlineConfig.rainbowColor ? ImGui::ColorConvertFloat4ToU32(GetRainbowColor(outlineTopLeftFactor)) :
											ImGui::ColorConvertFloat4ToU32(InterpolateLineColor(boxOutlineConfig.gradientStartColor, boxConfig.gradientEndColor, outlineTopLeftFactor));

										auto interpolatedBoxOutlineColorTopRight = boxOutlineConfig.rainbowColor ? ImGui::ColorConvertFloat4ToU32(GetRainbowColor(outlineTopRightFactor)) :
											ImGui::ColorConvertFloat4ToU32(InterpolateLineColor(boxOutlineConfig.gradientStartColor, boxOutlineConfig.gradientEndColor, outlineTopRightFactor));

										auto interpolatedBoxOutlineColorBottomLeft = boxOutlineConfig.rainbowColor ? ImGui::ColorConvertFloat4ToU32(GetRainbowColor(outlineBottomLeftFactor)) :
											ImGui::ColorConvertFloat4ToU32(InterpolateLineColor(boxOutlineConfig.gradientStartColor, boxOutlineConfig.gradientEndColor, outlineBottomLeftFactor));

										auto interpolatedBoxOutlineColorBottomRight = boxOutlineConfig.rainbowColor ? ImGui::ColorConvertFloat4ToU32(GetRainbowColor(outlineBottomRightFactor)) :
											ImGui::ColorConvertFloat4ToU32(InterpolateLineColor(boxOutlineConfig.gradientStartColor, boxOutlineConfig.gradientEndColor, outlineBottomRightFactor));


										auto chosenInterpolatedBoxOutlineColorTopLeft = boxOutlineConfig.distanceColor ?
											ImGui::ColorConvertFloat4ToU32(calculateColorBasedOnDistance(
												bodyPos,
												localPosition,
												boxOutlineConfig.minDistance,
												boxOutlineConfig.maxDistance,
												boxOutlineConfig.closeDistanceColor,
												boxOutlineConfig.farDistanceColor)) : interpolatedBoxOutlineColorTopLeft;

										auto chosenInterpolatedBoxOutlineColorTopRight = boxOutlineConfig.distanceColor ?
											ImGui::ColorConvertFloat4ToU32(calculateColorBasedOnDistance(
												bodyPos,
												localPosition,
												boxOutlineConfig.minDistance,
												boxOutlineConfig.maxDistance,
												boxOutlineConfig.closeDistanceColor,
												boxOutlineConfig.farDistanceColor)) : interpolatedBoxOutlineColorTopRight;

										auto chosenInterpolatedBoxOutlineColorBottomLeft = boxOutlineConfig.distanceColor ?
											ImGui::ColorConvertFloat4ToU32(calculateColorBasedOnDistance(
												bodyPos,
												localPosition,
												boxOutlineConfig.minDistance,
												boxOutlineConfig.maxDistance,
												boxOutlineConfig.closeDistanceColor,
												boxOutlineConfig.farDistanceColor)) : interpolatedBoxOutlineColorBottomLeft;

										auto chosenInterpolatedBoxOutlineColorBottomRight = boxOutlineConfig.distanceColor ?
											ImGui::ColorConvertFloat4ToU32(calculateColorBasedOnDistance(
												bodyPos,
												localPosition,
												boxOutlineConfig.minDistance,
												boxOutlineConfig.maxDistance,
												boxOutlineConfig.closeDistanceColor,
												boxOutlineConfig.farDistanceColor)) : interpolatedBoxOutlineColorBottomRight;

										auto chosenBoxOutlineColorTopLeft = boxOutlineStaticColor ? ImGui::ColorConvertFloat4ToU32(boxOutlineConfig.staticColor) : chosenInterpolatedBoxOutlineColorTopLeft;
										auto chosenBoxOutlineColorTopRight = boxOutlineStaticColor ? ImGui::ColorConvertFloat4ToU32(boxOutlineConfig.staticColor) : chosenInterpolatedBoxOutlineColorTopRight;
										auto chosenBoxOutlineColorBottomLeft = boxOutlineStaticColor ? ImGui::ColorConvertFloat4ToU32(boxOutlineConfig.staticColor) : chosenInterpolatedBoxOutlineColorBottomLeft;
										auto chosenBoxOutlineColorBottomRight = boxOutlineStaticColor ? ImGui::ColorConvertFloat4ToU32(boxOutlineConfig.staticColor) : chosenInterpolatedBoxOutlineColorBottomRight;

										if (boxOutlineConfig.fade) {
											chosenBoxOutlineColorTopLeft = ImGui::ColorConvertFloat4ToU32(calculateFadeBasedOnDistance(bodyPos, localPosition, boxOutlineConfig.fadeDistance, ImGui::ColorConvertU32ToFloat4(chosenBoxOutlineColorTopLeft)));
											chosenBoxOutlineColorTopRight = ImGui::ColorConvertFloat4ToU32(calculateFadeBasedOnDistance(bodyPos, localPosition, boxOutlineConfig.fadeDistance, ImGui::ColorConvertU32ToFloat4(chosenBoxOutlineColorTopRight)));
											chosenBoxOutlineColorBottomLeft = ImGui::ColorConvertFloat4ToU32(calculateFadeBasedOnDistance(bodyPos, localPosition, boxOutlineConfig.fadeDistance, ImGui::ColorConvertU32ToFloat4(chosenBoxOutlineColorBottomLeft)));
											chosenBoxOutlineColorBottomRight = ImGui::ColorConvertFloat4ToU32(calculateFadeBasedOnDistance(bodyPos, localPosition, boxOutlineConfig.fadeDistance, ImGui::ColorConvertU32ToFloat4(chosenBoxOutlineColorBottomRight)));
										}

										/// TODO: add rainbow and distance color to this shit

										// Inner outline with outlineThickness
										draw->AddRectFilledMultiColor(
											ImVec2(min.x + boxConfig.lineThickness, min.y + boxConfig.lineThickness),
											ImVec2(max.x - boxConfig.lineThickness, min.y + boxConfig.lineThickness + boxOutlineConfig.lineThickness),
											chosenBoxOutlineColorTopLeft, chosenBoxOutlineColorTopRight,
											chosenBoxOutlineColorTopRight, chosenBoxOutlineColorTopLeft
												);
												draw->AddRectFilledMultiColor(
													ImVec2(min.x + boxConfig.lineThickness, max.y - boxConfig.lineThickness - boxOutlineConfig.lineThickness),
													ImVec2(max.x - boxConfig.lineThickness, max.y - boxConfig.lineThickness),
													chosenBoxOutlineColorBottomLeft, chosenBoxOutlineColorBottomRight,
													chosenBoxOutlineColorBottomRight, chosenBoxOutlineColorBottomLeft
												);
												draw->AddRectFilledMultiColor(
													ImVec2(min.x + boxConfig.lineThickness, min.y + boxConfig.lineThickness),
													ImVec2(min.x + boxConfig.lineThickness + boxOutlineConfig.lineThickness, max.y - boxConfig.lineThickness),
													chosenBoxOutlineColorTopLeft, chosenBoxOutlineColorBottomLeft,
													chosenBoxOutlineColorBottomLeft, chosenBoxOutlineColorTopLeft
												);
												draw->AddRectFilledMultiColor(
													ImVec2(max.x - boxConfig.lineThickness - boxOutlineConfig.lineThickness, min.y + boxConfig.lineThickness),
													ImVec2(max.x - boxConfig.lineThickness, max.y - boxConfig.lineThickness),
													chosenBoxOutlineColorTopRight, chosenBoxOutlineColorBottomRight,
													chosenBoxOutlineColorBottomRight, chosenBoxOutlineColorTopRight
												);

												// Outer outline
												draw->AddRectFilledMultiColor(
													outlineMin,
													ImVec2(outlineMax.x, outlineMin.y + boxOutlineConfig.lineThickness),
													chosenBoxOutlineColorTopLeft, chosenBoxOutlineColorTopRight,
													chosenBoxOutlineColorTopRight, chosenBoxOutlineColorTopLeft
												);
												draw->AddRectFilledMultiColor(
													ImVec2(outlineMin.x, outlineMax.y - boxOutlineConfig.lineThickness),
													outlineMax,
													chosenBoxOutlineColorBottomLeft, chosenBoxOutlineColorBottomRight,
													chosenBoxOutlineColorBottomRight, chosenBoxOutlineColorBottomLeft
												);
												draw->AddRectFilledMultiColor(
													outlineMin,
													ImVec2(outlineMin.x + boxOutlineConfig.lineThickness, outlineMax.y),
													chosenBoxOutlineColorTopLeft, chosenBoxOutlineColorBottomLeft,
													chosenBoxOutlineColorBottomLeft, chosenBoxOutlineColorTopLeft
												);
												draw->AddRectFilledMultiColor(
													ImVec2(outlineMax.x - boxOutlineConfig.lineThickness, outlineMin.y),
													outlineMax,
													chosenBoxOutlineColorTopRight, chosenBoxOutlineColorBottomRight,
													chosenBoxOutlineColorBottomRight, chosenBoxOutlineColorTopRight
												);
									}

								}
								else { /// render only static

									float combinedFactorBody = (gradientFactor + positionFactorBody) / 2.0f;

									auto interpolatedBoxColor = InterpolateLineColor(boxConfig.gradientStartColor, boxConfig.gradientEndColor, combinedFactorBody);

									if (boxOutlineConfig.state) { // this code is shit, suck ya mum
										/// handle outline with color and shit

										bool boxOutlineStaticColor = (!boxOutlineConfig.gradientColor && !boxOutlineConfig.distanceColor) ? true : false;

										auto interpolatedBoxOutlineColor = boxOutlineConfig.rainbowColor ? GetRainbowColor(combinedFactorBody) :
											InterpolateLineColor(boxOutlineConfig.gradientStartColor, boxOutlineConfig.gradientEndColor, combinedFactorBody);

										auto chosenInterpolatedBoxOutlineColor = boxOutlineConfig.distanceColor ? calculateColorBasedOnDistance(
											bodyPos,
											localPosition,
											boxOutlineConfig.minDistance,
											boxOutlineConfig.maxDistance,
											boxOutlineConfig.closeDistanceColor,
											boxOutlineConfig.farDistanceColor) : interpolatedBoxOutlineColor;

										auto chosenBoxOutlineColor = boxOutlineStaticColor ? boxOutlineConfig.staticColor : chosenInterpolatedBoxOutlineColor;

										if (boxOutlineConfig.fade) {
											chosenBoxOutlineColor = calculateFadeBasedOnDistance(bodyPos, localPosition, boxOutlineConfig.fadeDistance, chosenBoxOutlineColor);
										}

										draw->AddRect(
											ImVec2(min + ImVec2(1, 1)),
											ImVec2(max - ImVec2(1, 1)),
											ImGui::ColorConvertFloat4ToU32(chosenBoxOutlineColor),
											boxConfig.rounding, 0, boxOutlineConfig.lineThickness);

										draw->AddRect(
											ImVec2(min - ImVec2(1, 1)),
											ImVec2(max + ImVec2(1, 1)),
											ImGui::ColorConvertFloat4ToU32(chosenBoxOutlineColor),
											boxConfig.rounding, 0, boxOutlineConfig.lineThickness);

									}

									// Main rectangle
									draw->AddRect(min, max, ImGui::ColorConvertFloat4ToU32(boxConfig.staticColor), boxConfig.rounding, 0, boxConfig.lineThickness);
								}
							}


							/// render tracer


							if (tracerConfig.state && ((player.isLocalPlayer && tracerConfig.renderSelf) || !player.isLocalPlayer)) {

								float time = ImGui::GetTime() * tracerConfig.gradientSpeed;
								float gradientFactor = fmodf(time, 2.0f);

								if (gradientFactor > 1.0f)
									gradientFactor = 2.0f - gradientFactor;

								float combinedFactorRightHand = (gradientFactor + positionFactorRightHand) / 2.0f;
								float combinedFactorLeftHand = (gradientFactor + positionFactorLeftHand) / 2.0f;
								float combinedFactorBody = (gradientFactor + positionFactorBody) / 2.0f;

								auto tracerStartColor = tracerConfig.gradientColor ? tracerConfig.gradientStartColor : tracerConfig.staticColor;
								auto tracerEndColor = tracerConfig.gradientColor ? tracerConfig.gradientEndColor : tracerConfig.staticColor;

								/// normal interpolation 
								/// pointless calc here but im too lazy to optimize this
								auto interpolatedColorBody = tracerConfig.rainbowColor ? GetRainbowColor(combinedFactorBody) : InterpolateLineColor(tracerStartColor, tracerEndColor, combinedFactorBody);

								// calculateColorBasedOnDistance

								auto chosenColorTracer = tracerConfig.distanceColor ?
									calculateColorBasedOnDistance(
										bodyPos,
										localPosition,
										tracerConfig.minDistance,
										tracerConfig.maxDistance,
										tracerConfig.closeDistanceColor,
										tracerConfig.farDistanceColor) : interpolatedColorBody;

								/// render skeleton

								if (tracerConfig.fade) {
									chosenColorTracer = calculateFadeBasedOnDistance(rightHandPos, localPosition, tracerConfig.fadeDistance, chosenColorTracer);
								}

								draw->AddLine(
									ImVec2(screenWidth / 2, screenHeight / 2),
									ImVec2(w2sBody.x, screenHeight - w2sBody.y),
									ImGui::ColorConvertFloat4ToU32(chosenColorTracer),
									tracerConfig.lineThickness
								);
							}

							/// render nametag

							if (nametagConfig.state && ((player.isLocalPlayer && nametagConfig.renderSelf) || !player.isLocalPlayer)) {
								std::string PlayerNameString;
								
								if (nametagConfig.showActorNumber) {
									PlayerNameString += " [" + std::to_string(player.photonActorID) + "] ";
								}
								
								PlayerNameString += player.DisplayName;

								if (nametagConfig.showPing) {
									PlayerNameString += " (" + std::to_string(playerPlayer->get_Ping()) + "ms)";
								}

								if (nametagConfig.showDistance) {
									float distance = bodyPos.distanceTo(localPosition);
									PlayerNameString += " (" + std::to_string(static_cast<int>(distance)) + "m)";
								}

								ImVec2 nametagSize = ImGui::CalcTextSize(PlayerNameString.c_str());
								ImVec2 nametagPos = ImVec2(w2sBody.x - nametagSize.x * 0.5f, screenHeight - w2sBody.y - nametagSize.y - -50.0f); // -50 offset

								ImVec2 padding = ImVec2(5.0f, 3.0f);
								ImVec2 additionalSize = ImVec2(2.0f, 2.0f);

								if (nametagConfig.showMasterClient && PhotonNetwork::get_isMasterClient(photonPlayer)) {
									additionalSize.x += ImGui::CalcTextSize("[M]=").x;
								}

								if (nametagConfig.showVMOD && IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID))) {
									additionalSize.x += ImGui::CalcTextSize("[VMOD]=").x;
								}

								if (nametagConfig.background) {
									float time = ImGui::GetTime() * nametagConfig.gradientSpeed;
									float gradientFactor = fmodf(time, 2.0f);

									if (gradientFactor > 1.0f)
										gradientFactor = 2.0f - gradientFactor;

									float combinedFactorRightHand = (gradientFactor + positionFactorRightHand) / 2.0f;
									float combinedFactorLeftHand = (gradientFactor + positionFactorLeftHand) / 2.0f;
									float combinedFactorBody = (gradientFactor + positionFactorBody) / 2.0f;

									auto tracerStartColor = nametagOutlineConfig.gradientColor ? nametagOutlineConfig.gradientStartColor : nametagOutlineConfig.staticColor;
									auto tracerEndColor = nametagOutlineConfig.gradientColor ? nametagOutlineConfig.gradientEndColor : nametagOutlineConfig.staticColor;

									/// normal interpolation 
									/// pointless calc here but im too lazy to optimize this
									auto interpolatedColorBody = nametagOutlineConfig.rainbowColor ? GetRainbowColor(combinedFactorBody) : InterpolateLineColor(tracerStartColor, tracerEndColor, combinedFactorBody);

									// calculateColorBasedOnDistance

									auto chosenOutlineColor = nametagOutlineConfig.distanceColor ?
										calculateColorBasedOnDistance(
											bodyPos,
											localPosition,
											nametagOutlineConfig.minDistance,
											nametagOutlineConfig.maxDistance,
											nametagOutlineConfig.closeDistanceColor,
											nametagOutlineConfig.farDistanceColor) : interpolatedColorBody;

									auto chosenBackgroundColor = nametagConfig.backgroundColor;

									if (nametagConfig.fade) {
										chosenOutlineColor = calculateFadeBasedOnDistance(rightHandPos, localPosition, nametagConfig.fadeDistance, chosenOutlineColor);
										chosenBackgroundColor = calculateFadeBasedOnDistance(rightHandPos, localPosition, nametagConfig.fadeDistance, chosenBackgroundColor);
									}

									ImVec2 bgMin = nametagPos - padding;
									ImVec2 bgMax = nametagPos + nametagSize + additionalSize + padding;

									draw->AddRectFilled(bgMin, bgMax, ImGui::ColorConvertFloat4ToU32(chosenBackgroundColor), nametagOutlineConfig.rounding); // Transparent black background
									draw->AddRect(bgMin, bgMax, ImGui::ColorConvertFloat4ToU32(chosenOutlineColor), nametagOutlineConfig.rounding, 0, nametagOutlineConfig.lineThickness); // White border
								}


								float extraOpacity = 1.0f;

								if (nametagConfig.fade) {
									extraOpacity = calculateFadeBasedOnDistance(bodyPos, localPosition, nametagConfig.fadeDistance, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)).w;
								}

								if (playerPlayer->get_IsFriend()) {
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.7f, 1.0f, 1.0f)); // Blueish
								}

								ImGui::SetCursorScreenPos(nametagPos);

								if (nametagConfig.gradientColor && nametagConfig.rainbowColor) {
									DrawOutlinedText(PlayerNameString.c_str());
									RainbowText(PlayerNameString.c_str(), nametagConfig.gradientSpeed, &nametagPos, 1.0f);
								}
								else if (nametagConfig.gradientColor) {

									//auto gradientStartColor = nametagConfig.fade ? ImVec4(nametagConfig.gradientStartColor.x, nametagConfig.gradientStartColor.y, nametagConfig.gradientStartColor.z, extraOpacity) : nametagConfig.gradientStartColor;
									//auto gradientEndColor = nametagConfig.fade ? ImVec4(nametagConfig.gradientEndColor.x, nametagConfig.gradientEndColor.y, nametagConfig.gradientEndColor.z, extraOpacity) : nametagConfig.gradientEndColor;
									DrawOutlinedText(PlayerNameString.c_str());
									GradientText(PlayerNameString.c_str(), nametagConfig.gradientSpeed, nametagConfig.gradientStartColor, nametagConfig.gradientEndColor, &nametagPos);
								}
								else if (nametagConfig.distanceColor) {


									auto distanceColor = calculateColorBasedOnDistance(bodyPos, localPosition, nametagConfig.minDistance, nametagConfig.maxDistance, nametagConfig.closeDistanceColor, nametagConfig.farDistanceColor);

									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(distanceColor.x, distanceColor.y, distanceColor.z, distanceColor.w)); // White
									DrawOutlinedText(PlayerNameString.c_str());
									ImGui::Text(PlayerNameString.c_str());
								}
								else {
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(nametagConfig.staticColor.x, nametagConfig.staticColor.y, nametagConfig.staticColor.z, nametagConfig.staticColor.w)); // White
									DrawOutlinedText(PlayerNameString.c_str());
									ImGui::Text(PlayerNameString.c_str());
								}

								if (nametagConfig.showMasterClient && PhotonNetwork::get_isMasterClient(photonPlayer)) {
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 1.0f, 1.0f)); // Purple
									DrawOutlinedText("[M]");
									ImGui::Text("[M]");
									ImGui::SetItemTooltip("Master Client.");
									ImGui::PopStyleColor();
								}

								if (nametagConfig.showVMOD && IsBlacklistedPlayerID(playerIdBlacklist, std::stoi(player.playerID))) {
									ImGui::SameLine();
									ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red
									DrawOutlinedText("[VMOD]");
									ImGui::Text("[VMOD]");
									ImGui::SetItemTooltip("Blacklisted Player.");
									ImGui::PopStyleColor();
								}

								ImGui::PopStyleColor();
							}


						}
					}
				}
			}
		}
		ImGui::End();
	}
}