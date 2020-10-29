// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巴特沃斯[2;37;0m[2;37;0m", ({"butterworth"}));        
        set("gender", "女性");                
        set("long", "一只朱雀[2;37;0m
它是侯平的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "verilog");
        set("owner_name", "侯平");
        set_temp("owner", "verilog");
        set_temp("owner_name", "侯平");
        ::setup();
}
