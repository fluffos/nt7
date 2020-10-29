// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m小毒鸟[2;37;0m[2;37;0m", ({"xdn"}));        
        set("gender", "女性");                
        set("long", "一只变异毒鸟。[2;37;0m
它是五毒子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wuduzi");
        set("owner_name", "五毒子");
        set_temp("owner", "wuduzi");
        set_temp("owner_name", "五毒子");
        ::setup();
}
