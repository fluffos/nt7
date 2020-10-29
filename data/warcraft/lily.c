// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m好汪[2;37;0m[2;37;0m", ({"zille"}));        
        set("gender", "男性");                
        set("long", "汪~呜呜～～[2;37;0m
它是莉莉的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lily");
        set("owner_name", "莉莉");
        set_temp("owner", "lily");
        set_temp("owner_name", "莉莉");
        ::setup();
}
