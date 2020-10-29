// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m天使之翼[2;37;0m[2;37;0m", ({"redflg"}));        
        set("gender", "男性");                
        set("long", "一只青色的龙。[2;37;0m
它是欧阳星云的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cwz");
        set("owner_name", "欧阳星云");
        set_temp("owner", "cwz");
        set_temp("owner_name", "欧阳星云");
        ::setup();
}
