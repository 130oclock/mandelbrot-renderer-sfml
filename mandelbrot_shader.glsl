uniform vec2 window_Shape;
uniform int MAX_ITERATIONS;


void main() {
    vec2 c = gl_FragCoord.xy / window_Shape;

    // Move (0, 0) to center of window.
    c = c - 0.5;

    // Adjust for aspect ratio.
    float aspect_ratio = window_Shape.y / window_Shape.x;
    c.y = c.y * aspect_ratio;

    c = c * 4.0;

    int i = 0;
    vec2 z = vec2(0.0);

    while (z.x * z.x + z.y * z.y < 4.0) {
        float tmp = z.x * z.x - z.y * z.y + c.x;
        z.y = 2.0 * z.x * z.y + c.y;
        z.x = tmp;

        if (i >= MAX_ITERATIONS) {
            gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
            return;
        }
        ++i;
    }

    float color = float(i) / float(MAX_ITERATIONS);

    gl_FragColor = vec4(color, color, color, 1.0);
}