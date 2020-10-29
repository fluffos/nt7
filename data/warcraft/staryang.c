// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "女性");                
        set("long", "123456[2;37;0m
它是阳秘汲汲的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "staryang");
        set("owner_name", "阳秘汲汲");
        set_temp("owner", "staryang");
        set_temp("owner_name", "阳秘汲汲");
        ::setup();
}
