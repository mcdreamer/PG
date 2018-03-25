uniform sampler2D texture;

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

	gl_FragColor = blur5(texture, gl_TexCoord[0].xy, sceneSize, vec2(1, 1));
}
