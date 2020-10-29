// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小马[2;37;0m[2;37;0m", ({"myma"}));        
        set("gender", "男性");                
        set("long", "小马[2;37;0m
它是妹纸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mydali");
        set("owner_name", "妹纸");
        set_temp("owner", "mydali");
        set_temp("owner_name", "妹纸");
        ::setup();
}
