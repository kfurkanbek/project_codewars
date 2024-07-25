/*

Description:

A function so that passing in RGB decimal values will result in a hexadecimal
    representation being returned.

Valid decimal values for RGB are 0 - 255.

Any values that fall out of that range must be rounded to the closest valid
    value.

The return value should always be 6 characters long, the shorthand with 3 will
    not work here.

Examples (input --> output):

255, 255, 255 --> "FFFFFF"
255, 255, 300 --> "FFFFFF"
0, 0, 0       --> "000000"
148, 0, 211   --> "9400D3"

*/

void rgb(int r, int g, int b, char hex[6 + 1]);
