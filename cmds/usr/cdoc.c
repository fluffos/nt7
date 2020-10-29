// c_doc.c 制作帮派文件

void doc_edit( string str );
int main( object me )
{
        if( !query("bunch", me) || query("bunch/level", me)<7 )
                return 0;
                
        me->edit( (: doc_edit :) );
        return 1;
}

void doc_edit( string str )
{
        write_file("/help/"+query("bunch/bunch_name", this_player()),str,1);
        return;
}


int help( object me )
{
        write( "
        c_doc: 帮主编写帮派文件。
        可在文件里编写帮规, 帮派历史, 等资料。
        玩家 help <帮派中文名称> 即可阅读帮派文件。

");
        return 1;
}
