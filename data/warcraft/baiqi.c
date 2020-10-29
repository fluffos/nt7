// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白龙马[2;37;0m[2;37;0m", ({"myma"}));        
        set("gender", "男性");                
        set("long", "一只白龙马[2;37;0m
它是白旗的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "baiqi");
        set("owner_name", "白旗");
        set_temp("owner", "baiqi");
        set_temp("owner_name", "白旗");
        ::setup();
}
