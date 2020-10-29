// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m蝙蝠车[2;37;0m[2;37;0m", ({"picca"}));        
        set("gender", "女性");                
        set("long", "多少点[2;37;0m
它是平安保险的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "picc");
        set("owner_name", "平安保险");
        set_temp("owner", "picc");
        set_temp("owner_name", "平安保险");
        ::setup();
}
