// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m皮娃娃[5m[1;37m霍启刚[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "这是淘宝热销的霍启刚版皮娃娃，裆下有神器，引众多少女竞脱裤。[2;37;0m
它是伏明霞的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "fmx");
        set("owner_name", "伏明霞");
        set_temp("owner", "fmx");
        set_temp("owner_name", "伏明霞");
        ::setup();
}
