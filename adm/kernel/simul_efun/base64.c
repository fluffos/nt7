// /adm/simul_efun/base64.c
// By find.

// 编码
string base64_encode(string ascii)
{
        if( !stringp(ascii) || (ascii == "") )
                return ascii;

        return BASE64_D->encode(ascii);
}

// 解码
string base64_decode(string b64)
{
        if( !stringp(b64) || (b64 == "") )
                return b64;

        return BASE64_D->decode(b64);
}
