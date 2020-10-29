string decode(string buff, int len)
{
    int i = 0;
    while (i < len)
    {
        buff[i] = ~((buff[i] << 4 & 0xF0) | (buff[i] >> 4 & 0x0F));
        i++;
    }
    return buff;
}

string test(string temp)
{
     string str = "";
    
    int size;
    size = 26;
    while( size > 0 )
    {
        str += decode(temp[0..25], sizeof(temp[0..25]));
        temp = temp[25..];
        size = sizeof(temp);
   }
    write(str+"\n");
    return str;
}

string ps(string arg)
{
    arg = test(arg);
    arg = test(arg);
    return arg;
}


/*
void decode_buffer (unsigned  char* buff,int size,int current_block)
{
    //对文件按字节解密;

    int i = 0;
    while (i < size)
    {
        buff[i] = ~((buff[i] << 4 & 0xF0) | (buff[i] >> 4 & 0x0F));
        i++;
    }
}
*/
