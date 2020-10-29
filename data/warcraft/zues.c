// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m可爱的[2;37;0m[2;37;0m", ({"lovely"}));        
        set("gender", "男性");                
        set("long", "可爱的一条小青龙[2;37;0m
它是叶绿风的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "zues");
        set("owner_name", "叶绿风");
        set_temp("owner", "zues");
        set_temp("owner_name", "叶绿风");
        ::setup();
}
