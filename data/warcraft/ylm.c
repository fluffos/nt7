// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大熊[2;37;0m[2;37;0m", ({"daxiong"}));        
        set("gender", "女性");                
        set("long", "大熊[2;37;0m
它是一粒米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ylm");
        set("owner_name", "一粒米");
        set_temp("owner", "ylm");
        set_temp("owner_name", "一粒米");
        ::setup();
}
