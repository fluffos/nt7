// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白龙马[2;37;0m[2;37;0m", ({"huoju"}));        
        set("gender", "男性");                
        set("long", "白龙马[2;37;0m
它是归来王者的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mudking");
        set("owner_name", "归来王者");
        set_temp("owner", "mudking");
        set_temp("owner_name", "归来王者");
        ::setup();
}
