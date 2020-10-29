// cloth.c
#include <armor.h>
inherit EQUIP;

int is_armor() { return 1; }
void setup()
{
        //if( !clonep(this_object()) )
                set("armor_type", TYPE_CLOTH);

        ::setup();
}

void init()
{
        add_action("do_tear", "tear");
}

int do_tear(string str)
{
        object ob;
        
        if( !id(str) ) return 0;
        
        if( (string)query("material") != "cloth" )
                return notify_fail("你只能撕布料的衣服。\n");
    
        if( (int)query("teared_count") >= 4 )
                return notify_fail( name() + "的袖口，下□已经没有多余的布可撕了。\n");
    
        message_vision("$N从" + name() + "撕下一条布条。\n", this_player() );       
        addn("teared_count", 1);
        ob = new("/clone/misc/bandage");
        ob->set_name("从" + name() + "撕下的布条", ({ "cloth piece", "piece", "cloth" }) );
        ob->move(this_player(), 1);
        return 1;
}

int washed(int n)
{
        switch( query("material") )
        {
        case "cloth":
                n += n * 3 / 10;
                break;
        case "leather":
                break;
        case "silk":
                n -= n * 3 / 10;
                break;
        case "bamboo":
                n -= n * 5 / 10;
                break;
        case "steel":
                n -= n * 7 / 10;
                break;
        }
        set_temp("no_wear", "现在" + name() + "还是湿乎乎的，你没法穿。\n");
        delete_temp("daub");
        remove_call_out("dry_cloth");
        if( n ) call_out("dry_cloth", n);
        return n;
}

void dry_cloth()
{
        if( !objectp(this_object()) )
                return;
        delete_temp("no_wear");
        message("vision", name() + "已经干了。\n", environment());
}
