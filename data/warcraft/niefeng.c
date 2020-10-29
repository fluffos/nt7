// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m埃其亚基[2;37;0m[2;37;0m", ({"ling_hu"}));        
        set("gender", "男性");                
        set("long", "这是一只纯白的老虎，在当地的语言中，它名字的意思是银色的风。[2;37;0m
它是聂锋的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "niefeng");
        set("owner_name", "聂锋");
        set_temp("owner", "niefeng");
        set_temp("owner_name", "聂锋");
        ::setup();
}
