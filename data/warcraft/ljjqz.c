// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m朱雀[1;31m赤炎[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "飞得快[2;37;0m
它是不知死的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ljjqz");
        set("owner_name", "不知死");
        set_temp("owner", "ljjqz");
        set_temp("owner_name", "不知死");
        ::setup();
}
