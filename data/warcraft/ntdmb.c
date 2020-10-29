// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是武当米二的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ntdmb");
        set("owner_name", "武当米二");
        set_temp("owner", "ntdmb");
        set_temp("owner_name", "武当米二");
        ::setup();
}
