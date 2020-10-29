// /kungfu/skill/qingshen-fa
// by dubei
// 如来轻身法

inherit SKILL;

string *dodge_msg = ({
           "$n使出一招「轻身似空」，身体陡转徐徐向上飘去。\n",
           "$n使出一招「明空如镜」，双足猛然向上弹起，跃至半空之中。\n",
           "$n使出一招「莲空」，身形一变，滑至$N身后。\n",
            "$n大吼一声，使出一招「大安空」，从$N头顶越过。\n",
            "$n使出一招「佛空」，如轻鸿般飘去，瞬间又闪至$N面前。\n",
             "$n使出一招「金刚空」，顿时$N周围都是$n的身影。\n",
 });


 
int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me) { return 1; }

string query_dodge_msg()
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( query("jingli", me)<50 )
                return notify_fail("你的体力太差了，不能练如来轻身法。\n");
        me->receive_damage("jingli", 30);
        return 1;
}

string perform_action_file(string action)
{       
               return __DIR__"qingshen-fa/" + action;
}