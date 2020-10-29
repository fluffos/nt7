#include <ansi.h>
#include <armor.h> 

inherit MEDAL; 
inherit F_NOCLONE;
inherit F_OBSAVE;

int is_medal_belt() { return 1; }
void create()
{
        set_name(HIM "勋章挂带" NOR, ({ "medal belt", "medal", "belt" }) );
        set_weight(10);

        set("unit", "张");
        set("long", HIM "一条勋章挂带。将各种勋章镶嵌(insert)在挂带上，装备挂带后即可发挥勋章特殊作用。\n" +
                    HIM "同时你也可以取下(take xunzhang)所有的镶嵌的勋章。\n" NOR);
        set("value", 100);
        set("armor_prop/armor", 1); 
        set("no_sell", 1);         
        
        if (! check_clone()) return 0;
        restore();
        setup();
}

void init() 
{
        if( this_player() == environment() ) 
        {
                add_action("do_insert", "insert"); 
                add_action("do_remove", "take"); 
        }
}

int do_insert(string arg)
{
        string file, filename, content;
        object me, ob;
        object tessera;
        mapping apply_prop, data;
        mapping *ins;
        string *apply;
        int i, n;
        
        me = this_player();
        ob = this_object();

        if( !arg || !objectp(tessera = present(arg, me)) )
                return notify_fail("你要镶嵌什么？\n");

        if( tessera == me )
                return notify_fail("你脑潮啊？\n");

        if( !tessera->is_xunzhang() )
                return notify_fail("你只能镶嵌勋章类物品！\n");

        if( query("equipped") )
                return notify_fail("你先将佩戴的勋章挂带解除下来再说！\n");
        
        if( me->query_skill("certosina", 1) < 200 )
                return notify_fail("你觉得你的镶嵌技艺还不够娴熟，不敢贸然动手。\n");

        if (sscanf(base_name(tessera), "/data/%*s"))
                return notify_fail("这类物品无法用来镶嵌。\n"); 
        
        if( query("enchase/medal" + query("enchase/SN", tessera)) )
                return notify_fail("勋章挂带已经镶嵌此勋章，不能重复镶嵌同种勋章。\n");
        
        apply_prop = query("armor_prop", tessera);
        if( !mapp(apply_prop) || sizeof(apply_prop) < 1 )  
                return notify_fail(tessera->name()+"已经是废弃的，镶嵌这个没有任何意义。\n");
                             
        message_vision( HIM "$N" HIM "将" + tessera->name() + NOR HIM"镶嵌到了$n" HIM "上面，\n只见上面$n"
                        HIM "隐隐的显过了一道奇异的光芒，随即变得平静，说不出的平凡。\n\n" NOR, me, this_object());
        tell_object(me, HIC "你感受勋章挂带发生了不可言喻的变化。\n" NOR);
        
        apply = keys(apply_prop);
        data  = copy(query("enchase/apply_prop"));
        if( !mapp(data) ) data = ([]);

        for( i = 0; i<sizeof(apply); i++ )
        {
                if ( undefinedp(data[apply[i]]) )
                        data[apply[i]] = apply_prop[apply[i]];
                else
                        data[apply[i]] += apply_prop[apply[i]];
        }

        set("enchase/apply_prop", data);
        set("enchase/medal"+query("enchase/SN", tessera), 1);
        ins = query("insert");
        if( !ins ) 
        {
                ins = ({});
        }
        ins += ({ ([ "file" : base_name(tessera),
                 "name" : query("name", tessera),
                 "id"   : query("id", tessera),
                 "SN"   : query("enchase/SN", tessera),
                 "armor_prop" : apply_prop ])
        });

        set("insert", ins);
        destruct(tessera);
        save();
        
        return 1;
}

int do_remove(string arg)
{
        mapping *ins;
        mapping enc;
        object belt;
        object me;
        object ob;
        int i, n;

        me = this_player();
        belt = this_object();
        
        if( !arg || arg != "xunzhang" )
                return notify_fail("你要取下什么？\n");

        if( base_name(belt) != "/data/item/belt/"+query("id", me) )
                return notify_fail("你只能取下你自己的勋章挂带上的勋章！\n");

        if( query("equipped", belt) )
                return notify_fail("你先将佩戴的勋章挂带解除下来再说！\n"); 

        ins = query("insert", belt); 
        if( !(n=sizeof(ins)) )
                return notify_fail("勋章挂带上没有镶嵌任何勋章！\n"); 
        
        for( i=0; i<n; i++ )      
        {
                enc = ins[i];
                if( undefinedp(enc["file"]) ) continue;
                ob = new(enc["file"]);
                ob->move(me, 1);
                tell_object(me, HIC "你从勋章挂带上取下一枚"+ob->name()+"。\n" NOR);
        }
        
        delete("enchase", belt);
        delete("insert", belt);

        save();
        
        return 1;
}

int receive_summon(object me)
{
        object env;

        if( (env = environment()) && env == me ) {
                write(name() + "不就在你身上嘛？你召唤个什么劲？\n");
                return 1;
        }

        if( env == environment(me) ) {
                message_vision(HIG "只见地上的" + name() +
                               HIG "化作一道光芒，飞跃至$N" HIW
                               "的掌中！\n\n" NOR, me);
        } else {
                if( env ) {
                        if( env->is_character() && environment(env) )
                                env = environment(env);

                        message("vision", HIG "突然" + name() + HIG "化作一道"
                                HIG "光芒消失了！\n\n" NOR, env);

                        if( interactive(env = environment()) ) {
                                tell_object(env, HIM + name() +
                                                 HIM "忽然离你而去了！\n" NOR);
                        }
                }

                message_vision(HIG "一道光芒划过，只见$N"
                               HIG "掌中多了一个$n" HIG "！\n\n" NOR,
                               me, this_object());
        }

        //move(me, 1);
        if( !this_object()->move(me) )
        {
                tell_object(me, HIR "由于你的负重太高，"+this_object()->name()+HIR "化作一道光芒，已然了无踪迹。\n" NOR);
                destruct(this_object());
                return 1;
        }
        this_object()->wear();
        return 1;
}

int hide_anywhere(object me)
{
        if( query("jingli", me)<100){
                tell_object(me, "你试图令" + name() +
                            "遁去，可是精力不济，难以发挥它的能力。\n");
                return 0;
        }
        addn("jingli", -100, me);

        message_vision(HIM "$N" HIM "轻轻一旋" + name() +
                       HIM "，已然了无踪迹。\n", me);
        save();
        destruct(this_object());
        return 1;
}

// 接受存盘数据的接口函数
int receive_dbase_data(mixed data)
{
        if( !mapp(data) )
                return 0;

        map_delete(data, "equipped");
        this_object()->set_dbase(data);

        return 1;
}

// 进行保存数据的接口函数
mixed save_dbase_data()
{
        mapping data;

        data = this_object()->query_entire_dbase();

        return data;
}

mixed query_autoload() { return (query("equipped") ? query("equipped") : "kept"); }
void autoload(string parameter)
{
        if( parameter == "worn" )
                this_object()->wear();
}

/*
void remove(string euid)
{
        save();
}
*/
