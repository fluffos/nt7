// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("五色金龙[2;37;0m[2;37;0m", ({"dex"}));        
        set("gender", "女性");                
        set("long", "没得描述[2;37;0m
它是圣骑士的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pal");
        set("owner_name", "圣骑士");
        set_temp("owner", "pal");
        set_temp("owner_name", "圣骑士");
        ::setup();
}
