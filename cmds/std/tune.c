// tune.c

inherit F_CLEAN_UP;

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}

int main(object me, string arg)
{
        int my_channels = query("channels", me), flag;
        mapping channels = fetch_variable("channels", get_object(CHANNEL_D));
        class channel_class ch;

        if( !arg )
        {
                tell(me, "你正在使用中的频道有："+CHANNEL_D->query_using_channel(me)+"。\n");
                return 1;
        }
        
        if( wizardp(me) && sscanf(arg, "-l %s", arg) ) flag = 1;

        if( undefinedp(ch = channels[arg]) || !classp(ch) )
                return notify_fail("没有这个频道。\n");

        if( !(ch->number & my_channels) && (wiz_level(me->query_id(1)) < ch->level) )
                return notify_fail("没有这个频道。\n");

        if( flag )
        {
                string *names;
                names = CHANNEL_D->query_channel_users(arg)->query_id(1);
                names = sort_array(names, 1);
                tell(me, "目前收听 " + arg + " 频道的共 " + sizeof(names) + " 人如下：\n");
                tell(me, sprintf("%-=80s", implode(names, ", ")) + ".\n");

                names = CHANNEL_D->query_channel_users(arg, 1)->query_id(1);
                names = sort_array(names, 1);
                tell(me, "其余 " + sizeof(names) + " 人如下：\n");
                tell(me, sprintf("%-=80s", implode(names, ", ")) + ".\n");
                return 1;
        }

        if( ch->number & my_channels )
        {
                set("channels", my_channels ^ ch->number, me);
                CHANNEL_D->remove_register(me, ch->number);
                tell(me, "关闭 "+arg+" 频道。\n");
        }
        else
        {
                set("channels", my_channels | ch->number, me);
                CHANNEL_D->register_channel(me, ch->number);
                tell(me, "开启 "+arg+" 频道。\n");
        }
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：tune [<频道名称>]

这个指令让你选择是否要收听某一频道的讯息，如果没有指定频道名称，就会列出
你目前收听中的频道，如果指定了频道，原来收听中的就会关掉，反之打开。

如果你对一个没有收听中的频道讲话，会自动将它打开。
要对一个频道讲话，只要用：

<频道名称> <讯息> ....

例子：
  chat hello everyone!

你可以用 help channels 查询目前有哪些频道可以收听。

see also : chat, rumor ...
HELP
        );
        return 1;
}
