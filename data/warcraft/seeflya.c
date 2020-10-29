// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m白小[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "小猫[2;37;0m
它是风飞一扬的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "seeflya");
        set("owner_name", "风飞一扬");
        set_temp("owner", "seeflya");
        set_temp("owner_name", "风飞一扬");
        ::setup();
}
