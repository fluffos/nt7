#include <ansi.h>
inherit F_CLEAN_UP; 

int main(object me, string str)
{
        mapping question;
        string code;
        object env;
        int ret;

                        env = environment(me);
                        if( env ) {
                                ret = "/adm/daemons/fubend"->enter_fuben_private(me, base_name(env));
                        }
                        if( ret ) {
                                tell_object(me,"你进入了私有副本。\n");
                        } else {
                                tell_object(me,"当前位置无法创建私有副本。\n");
                        }
                        return 1;
        if( str && sscanf(str, "answer %s", str) == 1 && sizeof(str) > 0 )
        {
                if( str == "giveup" )
                {
                        if( query("balance", me) < 5000000 )
                                return notify_fail("你的存款不足500两黄金，无法取消本次验证码。\n");
                        
                        addn("balance", -5000000, me);
                        delete_temp("fuben_captcha_code", me);

                        write("本次验证码取消成功。\n");
                        return 1;
                }
                if( str == query_temp("fuben_captcha_code", me) )
                {
                        delete_temp("fuben_captcha_code", me);

                        env = environment(me);
                        if( env ) {
                                ret = "/adm/daemons/fubend"->enter_fuben_private(me, base_name(env));
                        }
                        if( ret ) {
                                tell_object(me,"你进入了私有副本。\n");
                        } else {
                                tell_object(me,"当前位置无法创建私有副本。\n");
                        }
                        return 1;
                }
                else
                        return notify_fail("验证码输入错误。\n");
        }
        if( query_temp("fuben_captcha_code", me) )
        {
                write(HIY"\n请输入「fboss answer 验证码」以建立私有副本空间挑战boss。\n"NOR);
                return 1;
        }
        
        question = X_PointD->get_question();
        code = question["answer"];
        set_temp("fuben_captcha_code", code, me);
        write("\n验证码为：\n\n"NOR);
        write(question["question"]);
        write("\n输入「fboss answer 验证码」以建立私有副本空间挑战boss。\n"NOR);
        return 1;

}

