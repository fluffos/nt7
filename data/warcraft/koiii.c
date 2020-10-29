// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m烧鸡[2;37;0m[2;37;0m", ({"yiyayo"}));        
        set("gender", "男性");                
        set("long", "dfa[2;37;0m
它是米大菜偷的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "koiii");
        set("owner_name", "米大菜偷");
        set_temp("owner", "koiii");
        set_temp("owner_name", "米大菜偷");
        ::setup();
}
