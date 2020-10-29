// This program is a part of NITAN MudLIB
// Buddha2.c

#include <ansi.h>
inherit NPC;

#define BUDDHA  "/adm/npc/buddha"
int ask_recover();

void create()
{
        seteuid(getuid());
        set_name(HIY "释迦牟尼" NOR, ({ "buddha", "fo zu", "fo", "shijia muni" }));
        set("long", @LONG
佛祖庄严宝像，让人不敢正视。
LONG);
        set("nickname", HIW "三界法王" NOR);
        set("title", HIC "佛祖" NOR);
        set("gender", "男性" );
        set("age", 500);
        set("attitude", "friendly");
        set("max_jing", 1000099);
        set("max_qi", 1000099);
        set("max_jingli", 1000099);
        set("jingli", 1000099);
        set("max_neili", 1000099);
        set("neili", 1000099);
        set("jiali", 100009);
        set("str", 99);
        set("int", 99);
        set("con", 99);
        set("dex", 99);
        set("combat_exp", 100001000099);

        set("inquiry", ([
                "前世" : (: ask_recover :),
        ]));

        set_skill("dodge", 10000);
        set_skill("unarmed", 10000);
        set_skill("force", 10000);
        set_skill("parry", 10000);
        set_skill("sword", 10000);
        set_skill("medical", 10000);
        set_skill("literate", 10000);
        set_skill("lamaism", 10000);
        set_skill("buddhism", 10000);
        set_skill("shaolin-yishu", 10000);
        set_skill("idle-force", 10000);
        set_skill("huntian-baojian", 10000);
        set_skill("lunhui-jian", 10000);

        map_skill("force", "huntian-baojian");
        map_skill("parry", "lunhui-jian");
        map_skill("sword", "lunhui-jian");
        map_skill("medical", "shaolin-yishu");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "sword.hui" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),
        }));

        setup();
        carry_object("/clone/cloth/y-jiasha")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        add_action("do_recollect", "recollect");
}

int ask_recover()
{
        object me = this_player();

        command("look "+query("id", me));
        command("say 你与我前世有缘吗?");
        command("say 你可记得前世你姓甚名谁，我给你的揭语又是什么？");
        command("say 若你能答得上来我便给你开启前生全部记忆。");

        tell_object(me, HIW "佛祖在你耳边说道，若你想起来了就输入 recollect <id> <揭语> \n" NOR);
        return 1;
}

int do_recollect(string arg)
{
        string content, filename, item_filename;
        string my_id, my_name, id, pass;
        mapping all_skills, data, tmp_data, sum_data, my;
        string *sname, *sum;
        int i, n;
        object buddha, ob, me = this_player();

        if( query_temp("do_recollect") )
                return notify_fail("我现在正忙着，你请稍后片刻。\n");

        if( query("reborn/times", me) )
                return notify_fail("你的阿赖耶识不是已经打开了吗？");

        if( !arg || sscanf(arg, "%s %s", my_id, pass) != 2 )
                return notify_fail("你究竟记不记得自己前世是谁？\n");

        buddha = get_object(BUDDHA);
        data = buddha->query_reborn_data(my_id);
        if( !data ) return notify_fail("我怎么不记得前世跟你有缘呢？\n");

        if( data["reborn_pass"] != pass )
                return notify_fail("这句哪里是我给过的揭语！\n");

        if( data["reborn_time"]>query("birthday", me) )
                return notify_fail("此人转世之时你已在世上，你又怎么可能会是他今生投胎之躯？\n");

        if( data["gender"] != query("gender", me) )
                return notify_fail("你于此人转世之前的性别不一致，你怎么可能是他呢？\n");

        if( query("combat_exp", me) >= 100000000 )
                return notify_fail("你的经验受今世影响太深，我无法帮你打开阿赖耶识。\n");

        set_temp("do_recollect", 1);

        command("say 看来你果然是前世与我有缘之人，待我将你前世记忆打开！");

        message_vision( HIY "\n佛祖说着便朝着$N" HIY "轻轻一挥手。\n\n" NOR
                        HIR "$N" HIR "突然感到头痛欲裂......\n\n" NOR, me );

        my_name = data["name"];
        my = me->query_entire_dbase();

        all_skills = copy(data["all_skills"]);
        sname = keys(all_skills);
        n = sizeof(sname);
        for( i = 0; i < n; i++ )
                me->set_skill(sname[i], all_skills[sname[i]]);

        if( sizeof(data["reborn"]) )
        {
                tmp_data = copy(data["reborn"]);
                tmp_data["times"] += 1;
                tmp_data["time"] = copy(data["reborn_time"]);
                if( undefinedp(tmp_data["fams"]) ) tmp_data["fams"] = ({});
                tmp_data["fams"] += ({ data["family_name"] });
                tmp_data["id"] = my_id;
                tmp_data["name"] = my_name;
        }
        else
        {
                tmp_data  = ([ "times" : 1 ]);
                tmp_data += ([ "time" : data["reborn_time"] ]);
                tmp_data += ([ "fams" : ({ data["family_name"] }) ]);
                tmp_data += ([ "id" : my_id ]);
                tmp_data += ([ "name" : my_name ]);
        }
        my["reborn"] = tmp_data;
        my["can_make"] = copy(data["can_make"]);
        my["can_perform"] = copy(data["can_perform"]);
        my["can_exert"] = copy(data["can_exert"]);
        my["special_skill"] = copy(data["special_skill"]);
        my["horse"] = copy(data["horse"]);
        my["warcraft"] = copy(data["warcraft"]);
        my["jingmai"] = copy(data["jingmai"]);
        my["str"] = copy(data["str"]);
        my["int"] = copy(data["int"]);
        my["con"] = copy(data["con"]);
        my["dex"] = copy(data["dex"]);
        my["srv"] = copy(data["srv"]);
        my["NO_PK"] = copy(data["NO_PK"]);
        my["ability"] = copy(data["ability"]);
        my["ability1"] = copy(data["ability1"]);
        my["ability2"] = copy(data["ability2"]);
        my["newbie_mygift"] = copy(data["newbie_mygift"]);
        my["character"] = "国士无双";
        my["welcomegift"] = 1;
        my["tianfu"] = 0;
        delete("tianfu", me);

        if( mapp(data["member"]) ) {
                if( MEMBER_D->is_member(me) )
                        MEMBER_D->db_pay_member(me, data["member"]["money"]);
                else
                        MEMBER_D->db_create_member(me, data["member"]["money"]);

                MEMBER_D->db_fee_member(me, data["member"]["day"]);
                MEMBER_D->db_set_member(me, "vip", data["member"]["vip"]);
        }
        id=query("id", me);
        sum_data = copy(data["can_summon"]);
        sum = keys(sum_data);
        for( i = 0; i < sizeof(sum); i++ ) {
                filename = sum_data[sum[i]] + FILE_EXTENSION;
                if( file_size(filename) < 0 ) continue;
                if( sscanf(filename, "/data/template/%*s") )
                        set("can_summon/"+sum[i], sum_data[sum[i]], me);
                else {
                        if( id == my_id ) {
                                set("can_summon/"+sum[i], sum_data[sum[i]], me);
                                continue;
                        }
                        content = read_file(filename);
                        content=replace_string(content,my_id,id);
                        content=replace_string(content,my_name,query("name", me));
                        if( sum[i] == "qiankun" )
                                item_filename = ITEM_DIR + "cruise/" + id + FILE_EXTENSION;
                        else
                                item_filename = ITEM_DIR + id[0..0] + "/" + id +
                                        "-" + sum[i] + FILE_EXTENSION;
                        if( file_size(item_filename) != -1 )
                                write("已经存在原文件档案，现覆盖处理。\n");

                        assure_file(item_filename);
                        rm(item_filename);
                        if( !write_file(item_filename, content, 1) ) {
                                write("写入档案(" + filename + ")时出错，请通知巫师处理。\n");
                                return 0;
                        }

                        catch(call_other(item_filename, "???"));
                        ob = find_object(item_filename);

                        ob->receive_dbase_data(DBASE_D->query_object_data(filename));
                        set("user",query("name",  me)+"("+id+")", ob);
#ifdef DB_SAVE
                        DATABASE_D->db_remove_item(base_name(ob));
                        DATABASE_D->db_create_item(ob, ob->query_entire_dbase());
#endif
                        set("can_summon/"+sum[i], base_name(ob), me);
                        DBASE_D->clear_object(filename);
                        rm(filename);
                        ob->save();
                }
        }

        sum_data = copy(data["can_whistle"]);
        sum = keys(sum_data);
        for( i = 0; i < sizeof(sum); i++ ) {
                filename = sum_data[sum[i]] + FILE_EXTENSION;
                if( file_size(filename) < 0 ) continue;

                if( id == my_id ) {
                        set("can_whistle/"+sum[i], sum_data[sum[i]], me);
                        continue;
                }
                content = read_file(filename);
                content=replace_string(content,my_id,id);
                content=replace_string(content,my_name,query("name", me));

                item_filename = DATA_DIR + "warcraft/" + id + FILE_EXTENSION;

                if( file_size(item_filename) != -1 )
                        write("已经存在原文件档案，现覆盖处理。\n");

                assure_file(item_filename);
                rm(item_filename);
                if( !write_file(item_filename, content, 1) ) {
                        write("写入档案(" + filename + ")时出错，请通知巫师处理。\n");
                        return 0;
                }

                catch(call_other(item_filename, "???"));
                ob = find_object(item_filename);

                ob->receive_dbase_data(DBASE_D->query_object_data(filename));
#ifdef DB_SAVE
                DATABASE_D->db_remove_item(base_name(ob));
                DATABASE_D->db_create_item(ob, ob->query_entire_dbase());
#endif
                set("can_whistle/"+sum[i], base_name(ob), me);
                set("warcraft/file", base_name(ob), me);
                DBASE_D->clear_object(filename);
                rm(filename);
                ob->save();
        }

        log_file("static/reborn", sprintf("%s(%s) reborn from %s at %s.\n",
                 me->name(1),query("id", me),my_id,ctime(time())));

        if( query("reborn/times", me) == 1 )
        {
                set("xiantian_force", 1, me);
                tell_object(me, HIY "你终于脱凡入圣，可以修炼先天真气了。\n" NOR);
        } else
        if( query("reborn/times", me) == 2 )
        {
                set("yuanshen/attack", 10, me);
                set("yuanshen/defense", 10, me);
                set("yuanshen/damage", 10, me);
                set("yuanshen/armor", 10, me);
                set("yuanshen_exp", 1, me);
                set("yuanshen_level", 1, me);
                tell_object(me, HIY "你将精力化成元神，终于练得元神出世。\n" NOR);
        } else
        if( query("reborn/times", me) == 3 )
        {
                set("yuanshen/attack", 100, me);
                set("yuanshen/defense", 100, me);
                set("yuanshen/damage", 100, me);
                set("yuanshen/armor", 100, me);
                set("yuanshen_exp", 100000, me);
                set("yuanshen_level", 100, me);
                tell_object(me, HIY "你的元神终于可以突破瓶颈，可以继续修炼了。\n" NOR);
        }
        message("vision", HBRED "【转世重生】天界：据说有人已得佛祖恩典，开启了阿赖耶识。\n" NOR, users());
        me->save();
        me->unconcious();

        buddha->clear_reborn_data(my_id);
        buddha->save();
        delete_temp("do_recollect");
        return 1;
}
