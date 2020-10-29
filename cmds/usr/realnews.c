// realnews.c
// For Nt2
// Write by Hcifml

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
    return 1; 
    if(!arg)
        return help(me);
    if(arg == "list") 
        me->start_more(REALNEWS_D->read_news_list());
    else
        me->start_more(REALNEWS_D->read_news(arg));
    return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : realnews <list | 编号>
 
这个指令可以查看实时新闻，参数为list则显示所有新闻列表。
 
HELP
    );
    return 1;
}
