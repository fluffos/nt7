// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哦饿[2;37;0m[2;37;0m", ({"sdfdfe"}));        
        set("gender", "男性");                
        set("long", "哦饿[2;37;0m
它是胡三的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sandao");
        set("owner_name", "胡三");
        set_temp("owner", "sandao");
        set_temp("owner_name", "胡三");
        ::setup();
}
