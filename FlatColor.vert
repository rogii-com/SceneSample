attribute highp vec4 vertex;
uniform highp mat4 matrix;

void main()
{
    gl_Position = matrix * vertex;
}
