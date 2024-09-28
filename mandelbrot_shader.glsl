uniform float Width;
uniform float Height;


void main() {
    vec2 uv = vec2(gl_FragCoord.x / Width, gl_FragCoord.y / Height);

    // Scale everything within a circle of radius 2.
    uv = uv - 0.5;
    uv = uv * vec2(2, 2);

    // Adjust aspect ratio.
    float aspect_ratio = Width / Height;
    uv.x = uv.x * aspect_ratio;

    gl_FragColor = vec4(uv.x, 0.0, 0.0, 1.0);

    if (uv.x * uv.x + uv.y * uv.y < 2.0) {
        gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}