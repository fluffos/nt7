// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸡鸡[2;37;0m[2;37;0m", ({"xjj"}));        
        set("gender", "男性");                
        set("long", "不解释[2;37;0m
它是押运一的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yyga");
        set("owner_name", "押运一");
        set_temp("owner", "yyga");
        set_temp("owner_name", "押运一");
        ::setup();
}
