// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"team_with_libai"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是泥三的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "ntbc");
        set("owner_name", "泥三");
        set_temp("owner", "ntbc");
        set_temp("owner_name", "泥三");
        ::setup();
}
