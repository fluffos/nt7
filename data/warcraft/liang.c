// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m皮娃娃[5m[1;37m李泽楷[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "这是淘宝热销的李泽楷版皮娃娃，让你爽到爆，引无数少女争卖肾。[2;37;0m
它是梁洛施的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "liang");
        set("owner_name", "梁洛施");
        set_temp("owner", "liang");
        set_temp("owner_name", "梁洛施");
        ::setup();
}
