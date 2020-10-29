// edit.c

int edit(function callback, string text)
{
        if( !text ) text = "";

        write("结束离开用 '.'，取消输入用 '~q'，使用内建列编辑器用 '~e'。\n");
        write("—————————————————————————————\n");
        write(text);

        input_to("input_line", text, callback);
        return 1;
}

void input_line(string line, string text, function callback)
{
        if( line && query_temp("big5", this_player(1)) )
#ifdef LONELY_IMPROVED
                // line = B2G(line);
                line = LANGUAGE_D->Big52GB(line); 
#else
                line = LANGUAGE_D->Big52GB(line);
#endif
        if( line == "." ) {
                (*callback)(text);
                return;
        } else if( line == "~q" ) {
                write("输入取消。\n");
                return;
        } else if( line == "~e" ) {
        } else
                text += line + "\n";
        input_to("input_line", text, callback);
}

