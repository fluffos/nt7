// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("张扬[2;37;0m[2;37;0m", ({"zhangyanga"}));        
        set("gender", "女性");                
        set("long", "张扬[2;37;0m
它是毛毛宝宝的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "forredb");
        set("owner_name", "毛毛宝宝");
        set_temp("owner", "forredb");
        set_temp("owner_name", "毛毛宝宝");
        ::setup();
}
