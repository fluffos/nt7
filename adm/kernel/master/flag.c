// This program is a part of NT MudLIB

// 处理驱动程式启动时所指定的 mudlib 特定旗标
// 用来 debug... 平时无需载入
void flag( string arg )
{
        string file, func;
        if( previous_object() ) return;

        if( sscanf(arg,"load:%s %s",file,func) )
                printf( "MASTER: "+file+"'s "+func+"() 回传"+call_other(file, func) );
        else
                printf( "MASTER: 未知旗标\n" );
        return;
}
