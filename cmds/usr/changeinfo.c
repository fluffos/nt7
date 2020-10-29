#include <ansi.h>

#define CH_ID           (1<<0)
#define CH_NAME         (1<<1)

#define DEFAULT         CH_ID | CH_NAME
#define HELP            "/cmds/usr/color"

inherit F_CLEAN_UP;

string help = @HELP
更改使用者资讯

此指令可用来更改使用者资讯如下：

-i      修改玩家英文代号色彩
-n      修改玩家中文名称及色彩

如不加参数则表示全部修改

指令格式:
changeinfo [-i] [-n]

相关指令: finger, nick
HELP;

protected void change_prompt(object me, int flag);
protected void change_input(object me, int flag, string arg);

int main(object me, string arg)
{
        int flag;
        
#ifndef NO_FEE
        if ( !me->is_vip() )
                return notify_fail("你不是会员,无权使用该指令。\n");
#endif
                
        if( arg )
        {
                if( sscanf(arg, "%*s-i%*s", arg) == 2 ) flag |= CH_ID;
                if( sscanf(arg, "%*s-n%*s", arg) == 2 ) flag |= CH_NAME;
        }
        if( !flag ) flag = DEFAULT;
        tell_object(me, "跳过请输入 [ENTER]，取消请输入 '~q'，色彩协助请输入 '~h'\n");
        tell_object(me, WHT"["HIW"Change Information"NOR + WHT"]————————————————\n"NOR);
        change_prompt(me, flag);
        return 1;
}
protected void change_prompt(object me, int flag)
{
        if( flag & CH_ID )
        {
                tell_object(me,"\nID-["+query("id", me)+"]\n");
                tell_object(me, "请输入你的彩色英文代号：");
                input_to( (: change_input, me, flag :), 2 );
        }
        else if( flag & CH_NAME )
        {
                tell_object(me,"\nNAME-["+query("name", me)+"]\n");
                tell_object(me, "请输入你的彩色中文名称：");
                input_to( (: change_input, me, flag :), 2 );
        }

        return;
}
protected void change_input(object me, int flag, string arg)
{
        string *res;
        string text;
        
        text = arg;
        arg = filter_color(arg);

        if( arg && query_temp("big5", me) )
                text = LANGUAGE_D->Big52GB(text);

        if( !arg ) arg = "";

        if( arg == "~q" )
        {
                tell_object(me, "取消输入。\n");
                return;
        }
        if( arg == "~h" )
        {
                HELP->main(me);
                return change_prompt(me, flag);
        }
        if( flag & CH_ID )
        {
                if( arg == "" )
                        tell_object(me, "跳过彩色英文代号设定。\n");
                else
                {
                        if( !(res = me->set_idname(text, 0)) )
                        {
                                tell_object(me, "新设定的英文代号与原有英文代号不同，请重新设定。\n");
                                return change_prompt(me, flag);
                        }
                        tell_object(me, "彩色英文代号 '"+ res[0] +"' 设定完成。\n");
                }
                flag ^= CH_ID;
        }
        else if( flag & CH_NAME )
        {
                int len;

                if( arg == "" )
                        tell_object(me, "跳过彩色中文名称设定。\n");
                else
                {
                        arg = filter_color(trans_color(text,3),1);
                        len = strlen(arg);
                        if( len > 10 || len < 2 )
                        {
                                tell_object(me, "中文名称必须在 1 到 5 个中文字之间，请重新设定。\n");
                                return change_prompt(me, flag);
                        }
                        if (! is_chinese(filter_color(arg)))
                        {
                                tell_object(me, "请使用「中文」取名字，请重新设定。\n");
                                return change_prompt(me, flag);
                        }

                        if( !(res = me->set_idname(0, text)) )
                        {
                                tell_object(me, "新设定的中文名称与原有中文名称不同，请重新设定。\n");
                                return change_prompt(me, flag);
                        }
                        tell_object(me, "彩色中文名称 '" + res[1] + "' 设定完成。\n");
                }
                flag ^= CH_NAME;
        }

        if( flag ) return change_prompt(me, flag);
        return;
}

int help()
{
        write(@HELP
更改使用者资讯

此指令可用来更改使用者资讯如下：

-i      修改玩家英文代号色彩
-n      修改玩家中文名称及色彩

如不加参数则表示全部修改

指令格式:
changeinfo [-i] [-n]

相关指令: finger, nick
HELP);
        return 1;
}