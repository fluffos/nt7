// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸟[2;37;0m[2;37;0m", ({"niao"}));        
        set("gender", "女性");                
        set("long", "小鸟[2;37;0m
它是桃子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tzi");
        set("owner_name", "桃子");
        set_temp("owner", "tzi");
        set_temp("owner_name", "桃子");
        ::setup();
}
