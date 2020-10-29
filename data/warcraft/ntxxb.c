// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是星宿二号的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ntxxb");
        set("owner_name", "星宿二号");
        set_temp("owner", "ntxxb");
        set_temp("owner_name", "星宿二号");
        ::setup();
}
