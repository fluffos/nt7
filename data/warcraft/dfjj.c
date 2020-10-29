// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m渣冲[2;37;0m[2;37;0m", ({"zha"}));        
        set("gender", "男性");                
        set("long", "令狐渣冲[2;37;0m
它是东方姐姐的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dfjj");
        set("owner_name", "东方姐姐");
        set_temp("owner", "dfjj");
        set_temp("owner_name", "东方姐姐");
        ::setup();
}
