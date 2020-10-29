// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("拉布拉多[2;37;0m[2;37;0m", ({"kwride"}));        
        set("gender", "男性");                
        set("long", "这是一条纯种拉布拉多[2;37;0m
它是王战贰号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kingwarb");
        set("owner_name", "王战贰号");
        set_temp("owner", "kingwarb");
        set_temp("owner_name", "王战贰号");
        ::setup();
}
