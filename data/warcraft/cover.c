// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m轮椅[2;37;0m[2;37;0m", ({"booo"}));        
        set("gender", "男性");                
        set("long", "$HIW$轮椅[2;37;0m
它是别打脸的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cover");
        set("owner_name", "别打脸");
        set_temp("owner", "cover");
        set_temp("owner_name", "别打脸");
        ::setup();
}
