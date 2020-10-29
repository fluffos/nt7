


#include <ansi.h>
#include <emotion.h>

inherit F_CLEAN_UP;

#define BAR     "--------------------------------------------------------------------------------\n"

string help = @HELP
表情查询指令

这个指令会列出目前所有可以使用的表情指令

指令格式:
semote
semote -t               查看表情指令的使用排行表
semote -l               查看表情指令的简易说明
semote <表情代号>       查看 <表情代号> 的详细表情讯息


相关指令: command
HELP;

int help(object me)
{

        write(help);
        return 1;
}


private string replace_keys(string description)
{

        description = replace_string(description, "$ME", HIC"你"NOR);
        description = replace_string(description, "$YOU", HIG"某人"NOR);
        description = replace_string(description, "$T", HIM"事物"NOR);

        return description;
}

int main(object me, string arg)
{
        string msg;

        if( arg == "-t" )
        {
                int i;
                string *emotions = EMOTE_D->query_emotions();
                mapping emotion_sort = allocate_mapping(sizeof(emotions));

                foreach( string e in emotions )
                emotion_sort[e] = EMOTE_D->query_emotion(e)[USE];

#ifdef  __PACKAGE_ARITH_OPERATOR__
                emotions = sort_array(emotions, (: count( $(emotion_sort)[$1],">",$(emotion_sort)[$2] )? -1:1:));
#else
                emotions = sort_array(emotions, (: emotion_sort[$1]>emotion_sort[$2]? -1:1:));
#endif

                msg = "表情指令使用排名:\n";
                foreach( string e in emotions )
#ifdef  __PACKAGE_ARITH_OPERATOR__
                        msg += sprintf("%4s %-20s %-10s 次\n", HIW+(++i)+"."NOR, e, emotion_sort[e]);
#else
                        msg += sprintf("%4s %-20s %-10d 次\n", HIW+(++i)+"."NOR, e, emotion_sort[e]);
#endif

                me->start_more(msg+"\n");
                return 1;
        }
        else if( arg == "-l" )
        {
                int i;
                string *emotions = EMOTE_D->query_emotions();
                mapping emotion_sort = allocate_mapping(sizeof(emotions));

                foreach( string e in emotions )
                emotion_sort[e] = EMOTE_D->query_emotion(e)[NOTE];

                emotions = sort_array(emotions, (: strcmp($1, $2) :));

                msg = "表情指令简介说明\n";
                foreach( string e in emotions )
                {
                        msg += sprintf("%4s %-20s %-10s\n", HIW+(++i)+"."NOR, e, emotion_sort[e]||WHT"无简介"NOR);
                }
                me->start_more(msg+"\n");
                return 1;
        }
        else if( arg )
        {
                string *emotion = EMOTE_D->query_emotion(arg);

                if( undefinedp(emotion) )
                        return tell(me, "没有 " + arg + " 这个表情指令。\n", "CMDMSG");

                msg = "表情 "+arg+" 之详细叙述如下：\n"BAR;

                msg += NOR WHT"1.无对象无附加文字    ："NOR+replace_keys(emotion[NONE_ALL])+"\n";
                msg += NOR WHT"2.无对象有附加文字    ："NOR+replace_keys(emotion[NONE_ALL_ARG])+"\n";
                msg += NOR WHT"3.对象为自己无附加文字："NOR+replace_keys(emotion[ME_ALL])+"\n";
                msg += NOR WHT"4.对象为自己有附加文字："NOR+replace_keys(emotion[ME_ALL_ARG])+"\n";
                msg += NOR WHT"5.对象为某人无附加文字："NOR+replace_keys(emotion[YOU_ALL])+"\n";
                msg += NOR WHT"6.对象为某人有附加文字："NOR+replace_keys(emotion[YOU_ALL_ARG])+"\n";
                msg += NOR WHT"7.表情注解            ："NOR+(emotion[NOTE] || "无注解")+"\n";
                msg += NOR WHT"8.使用次数            ："NOR+emotion[USE]+" 次\n";
        }
        else
        {
                int size;
                string *emotions = sort_array(EMOTE_D->query_emotions(), 1);

                size = sizeof(emotions);
                msg = "目前共有 "+size+" 种表情指令可以使用，列表如下：\n"BAR;

                msg += sprintf("%-=80s", sprintf("%@-:10s", emotions)) + "\n";
                msg += "\n请输入 semote <表情代号> 观看详细叙述。\n";
        }

        me->start_more(msg + BAR);

        return 1;
}
