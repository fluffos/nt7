// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m关关[2;37;0m[2;37;0m", ({"kwankwan"}));        
        set("gender", "男性");                
        set("long", "这是一只关关[2;37;0m
它是奴才六号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "kwansix");
        set("owner_name", "奴才六号");
        set_temp("owner", "kwansix");
        set_temp("owner_name", "奴才六号");
        ::setup();
}
