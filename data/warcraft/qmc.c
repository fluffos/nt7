// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m永恒红兽[2;37;0m[2;37;0m", ({"qmcc"}));        
        set("gender", "女性");                
        set("long", "永恒红兽[2;37;0m
它是明教弟子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qmc");
        set("owner_name", "明教弟子");
        set_temp("owner", "qmc");
        set_temp("owner_name", "明教弟子");
        ::setup();
}
