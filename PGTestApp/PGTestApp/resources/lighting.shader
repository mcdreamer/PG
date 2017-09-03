uniform sampler2D texture;
uniform vec2 sceneSize;
uniform vec2 sceneOffset;
uniform float ambientLight;
uniform vec2 lightPts[3];
uniform float lightRadii[3];


vec4 blur5(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.3333333333333333) * direction;
  color += texture2D(image, uv) * 0.29411764705882354;
  color += texture2D(image, uv + (off1 / resolution)) * 0.35294117647058826;
  color += texture2D(image, uv - (off1 / resolution)) * 0.35294117647058826;
  return color;
}

void main()
{
	vec2 coords = vec2(gl_TexCoord[0].x, gl_TexCoord[0].y);

	vec4 pixel = texture2D(texture, coords);

	vec2 sceneCoords = vec2((coords.x * sceneSize.x) - sceneOffset.x, sceneOffset.y + (coords.y * sceneSize.y));

	float l = 0.0;
	for (int i = 0; i < 2; ++i)
	{
		vec2 toLight = vec2((sceneCoords.x - lightPts[i].x), (sceneCoords.y - lightPts[i].y));

		// float lighting = clamp((lightRadii[i] - length(toLight)) / lightRadii[i], 0.0, 1.0);

		float a = degrees(atan(toLight.y, toLight.x));
		if (toLight.y < 0.0)
		{
			a += 360.0;
		}

		if (a > 45.0 && a < 135.0)
		{
			float distance = (lightRadii[i] - length(toLight));
			if (distance > 0.0)
			{
				float lighting = 0.8;

				// float smoothDistance = 20.0;
				// if (distance < smoothDistance)
				// {
				// 	lighting *= distance / smoothDistance;
				// }

				l = l + lighting;
			}
		}
	}

	// gl_FragColor = blur5(texture, gl_TexCoord[0].xy, sceneSize, vec2(1, 1));//gl_Color * pixel * max(clamp(l, 0.0, 1.0), ambientLight);
	gl_FragColor = gl_Color * pixel * max(clamp(l, 0.0, 1.0), ambientLight);
}
