// /d/yixing/npc/bangzhu_duty.h
// Last Modified by Lonely on Jul. 12 2002
// duty 1   to accept players

int ask_join()
{
        object ob = this_player(), obj;
        string myfam, ob_fam;
        int exp=query("combat_exp", ob);

        ob_fam=query("family/family_name", ob);

        if( ob_fam == "丐帮" )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "一定是丐帮派来卧底的吧！\n");
                return 1;
        }

        if( ob_fam == "大理段家" )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "一定是大理国派来卧底的吧！\n");
                return 1;
        }

        if( ob_fam == "武当派" || ob_fam == "峨嵋派" || ob_fam == "华山派" ||
                ob_fam == "少林派" || ob_fam == "南少林派" )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "一定是名门正派派来卧底的吧！\n");
                return 1;
        }

        myfam = (string)query("party/party_name");
        if( query("party/party_name", ob) == myfam )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "！竟敢开帮主的玩笑！！！\n");
                return 1;
        }
        if( exp > query("combat_exp") && !wizardp(ob))
        {
                say(name() + "双手一抱拳道：" + RANK_D->query_respect(ob) + "莫非是开玩笑吧。\n");

                return 1;
        }
        if( time()<query("party/entertime", ob)+600 )
        {
                say(name() + "大怒道：" + RANK_D->query_rude(ob) + "，你如此反复无常岂能容身于江湖！！！\n");
                return 1;
        }
        message_vision("$N重重地拍了一下$n的肩膀，喝道：好样的！从今以后跟兄弟们有难同当！\n", this_object(), ob);

        ob->set_temp("apply/short",
                ({ HIR + myfam + "帮众"NOR + query("name",ob)+"("+capitalize(query("id",ob))+")" }));
        delete("party", ob);
        set("party/party_name", myfam, ob);
        set("party/entertime", time(), ob);

        if( obj = present("bang ling", ob) )
                destruct(obj);

        obj = new(BANGLING);
        set("owner",query("id",  ob), obj);
        set("fam", myfam, obj);
        set("combat_exp", query("combat_exp"), obj);
        obj->set("long",
"这是"+myfam+"的帮令，上面刻着「"+query("name", ob)+"」。\n");
        obj->move(ob);
        message_vision("$N把一"+query("unit", obj)+obj->name()+"扔给$n。\n",this_object(),ob);

        log_file("test/BangJoin",sprintf("%s于%s时加入%s\n",query("name", ob),ctime(time()),myfam));
        return 1;
}
#include "guanjia.h"
// duty 2  assign jobs
/*
string ask_job()
{
        object me = this_player(), leader, ling, ob, *obj, dest, room;
        string myfam, *files, file, region, biaoju, ob_bang;
        string *mydests, mydest, *starts;
        int i, temp, myexp;
        mapping job, destine;

        string *levels = ({
                "3000",
                "5000",
               "10000",
               "20000",
               "50000",
              "100000",
              "300000",
              "500000",
        });

        myfam = (string)query("fam");
        if( query_temp("bangs/fam", me) != myfam )
                return RANK_D->query_rude(me) + "莫非是想打听我帮的秘密吧。";

        if( objectp(leader = me->query_leader()) ) {
                if( leader != this_object() )
                         return RANK_D->query_rude(me) + "！入了帮不跟帮主跟别人
？！";
        }

        if( !(ling = present("bang ling", me)) ) {
                ling = new(BANGLING);
                set("owner",query("id",  me), ling);
                set("fam", myfam, ling);
                set("combat_exp", query("combat_exp"), ling);
                ling->move(me);
                message_vision("$N把一"+query("unit", ling)+ling->name()+"扔给$n。\n",this_object(),me);
        }

        if( time()<query("bangs/asktime", me)+180){
                if( mapp(query("job", ling)) )
                        return RANK_D->query_rude(me) + "不是刚问过我吗？";
        }

        set("bangs/asktime", time(), me);

        myexp=query("combat_exp", me);
        myexp = (4 * myexp + random(2 * myexp)) / 5;

        temp = sizeof(levels);
        for( i = 0; i < temp; i++ ) 
                if( myexp < atoi(levels[i]) ) break;

        if( i >= temp )
                return "最近没有适合你的帮务。";

        job = (BANGJOB + levels[i])->query_job();

        if( mapp(query("job", ling)) )
                delete("job", ling);
        set("job", job, ling);

        if( ob = present("caili", me) )
                destruct(ob);

        switch(job["type"]) {
        case "寻":
                command("nod");
                set("job/max", atoi(levels[i]), ling);
                return "你去把" + job["name"] + "找来。";
                break;

        case "杀":
                command("nod");
                set("job/max", atoi(levels[i]), ling);
                return "你去把" + job["area"] + "的" + job["name"] + "杀了。";
                break;

        case "摊费":
                command("nod");
                job = info_store[random(sizeof(info_store))];
                set("job/name", job["name"], ling);
                set("job/boss", job["boss"], ling);
                set("job/place", job["place"], ling);
                return job["name"] + "这个月还没有交摊费，快去要来！";
                break;

        case "截镖":
                obj = filter_array(children(BIAOTOU), (: clonep :));
                if( sizeof(obj) < 10 ) {
                        ob = new(BIAOTOU);
                        file = biao_places[random(sizeof(biao_places))];
                        if( !(dest = find_object(file)) )
                                dest = load_object(file);
                        ob->move(dest);            
                        message("vision",
                        ob->name() + "押着镖车走了过来。\n",
                        dest, ({ob}));
                        region = explode(file, "/")[1];
                        set("job/name",query("nickname",  ob), ling);
                        return "去踩盘的弟兄们回来讲，" + 
                        query("nickname", ob)+
                        "的镖车将经过" + 
                        region_names[region]+query("short", dest)+"。";
                } else {
                        ob = obj[random(sizeof(obj))];
                        dest = environment(ob);
                        biaoju=query("nickname", ob);

                        if( !dest || !biaoju ) {
                                destruct(ob);
                                command("shake");
                                return "你歇着吧，最近没有要紧的帮务。";
                        }

                        file = base_name(dest);
                        if( strsrch(file, "/d/") != 0
                         || !mapp(query("exits", dest))){
                                destruct(ob);
                                command("shake");
                                return "你歇着吧，最近没有要紧的帮务。";
                        }

                        command("nod");
                        region = explode(file, "/")[1];
                        set("job/name", biaoju, ling);
                        return "去踩盘的弟兄们回来讲，" + biaoju + 
                        "的镖车将经过" + 
                        region_names[region]+query("short", dest)+"。";
                }
                break;

        case "示威":
                obj = filter_array(children(BANGZHONG), (: clonep :));
                if( sizeof(obj) ) {
                obj = filter_array(obj, "is_victim", this_object(), myfam);
                if( sizeof(obj) ) {
                        command("nod");
                        ob = obj[random(sizeof(obj))];
                        ob_bang=query("title", ob);
                        set_temp("bangs/victim", ob_bang, me);
                        set("job/name", ob_bang, ling);
                        return "最近" + ob_bang + "经常跟我们过不去，你去杀一个示示威！";
                }
                }
                break;

        case "送礼":
                command("nod");

                job = info_guest[random(sizeof(info_guest))];
                region = explode(job["file"], "/")[1];

                ob = new(CAILI);
                set("job", job, ob);
                set("owner", me, ob);
                set("job/title", job["title"], ling);
                set("job/area", job["area"], ling);
                ob->set("long",
"这是一份" + myfam + "帮主送给" + "「" + job["title"] + "」" + "的彩礼。\n");
                ob->move(me);
                message_vision("$N将一"+query("unit", ob)+ob->name()+"交给$n。\n",this_object(),me);
                return "你把这份彩礼送给" + job["area"] + "的" + "「" + job["title"] + "」" + "。";
                break;

        case "护驾":
                region = explode(base_name(environment()), "/")[1];
                starts = keys(info_destine);
                if( member_array(region, starts) == -1 ) {
                        command("shake");
                        return "你歇着吧，最近没有要紧的帮务。";
                }
                destine = info_destine[region];
                mydests = keys(destine);
                mydest = mydests[random(sizeof(mydests))];
                set("job/dest", region_names[mydest], ling);
                set("job/bonus", destine[mydest], ling);
                ob = new(BANGZHU2);
                set("name", query("name"), ob);
                set("fam", myfam, ob);
                set("title", myfam+"帮主", ob);
                set("dest", mydest, ob);
                ob->set_leader(me);
                set("helper", me, ob);
                command("nod");
                call_out("do_start", 1, this_object(), ob);
                return "说道：我最近身体不适，你护送我至" + region_names[mydest] + "。\n";
        }

        command("shake");
        return "你歇着吧，最近没有要紧的帮务。";
}

void do_start(object me, object ob)
{
        ob->move(environment());
        destruct(this_object());
}

// duty 3  accept stuffs

int accept_object(object who, object ob)
{
        object obj;
        int bonus, record;
        string name, chname = "";
        mapping job;

        if( query_temp("bangs/fam", who) != query("fam") )
                return notify_fail(name() + "大怒道：大胆！想谋害本帮主！！！\n");

        if( !(obj = present("bang ling", who)) )
                return notify_fail(name() + "大怒道：没有用的东西，连帮令都会搞丢？！\n");

        if( !mapp(job=query("job", obj)) )
                return notify_fail(name() + "大怒道：没有用的东西，连自己的帮务都记不住？！\n");

        switch(job["type"]) {
        case "寻":
                name = ob->name();
                for(int i = 0; i < strlen(name); i++)
                        if(name[i] > 160 && name[i] < 255) 
                                chname += name[i..i];
                if( chname != job["name"] )
                        return notify_fail(name() + "大怒道：没有用的东西，连自己的帮务都记不住？！\n");
                bonus=job["bonus"]*job["max"]/(query("combat_exp", who)+1000);
                record = bonus / 2 + random(bonus);
                log_file("test/BangJob",sprintf("%s于%s时找到%s得%s经验点\n",query("name", who),ctime(time()),chname,chinese_number(record)));
                bonus = job["score"];
                break;

        case "截镖":
                if( base_name(ob) != BIAOHUO )
                        return notify_fail(name() + "大怒道：没有用的东西，连一枝镖都搞不定！\n");
                if( query("my_killer", ob) != query("id", who) )
                        return notify_fail(name() + "大怒道：江湖中最讲究的就是信用，再欺世盗名就宰了你！\n");
                bonus=query("combat_exp", ob);
                bonus=bonus*120/(bonus+query("combat_exp", who));
                record = bonus + random(bonus);
                log_file("test/BangJob",sprintf("%s于%s时因截镖得%s经验点\n",query("name", who),ctime(time()),chinese_number(record)));
                bonus /= 4;
                break;
        default:
                return notify_fail(name() + "大怒道：没有用的东西，连自己的帮务都记不住？！\n");
                break;
        }

        command("nod");
        delete("job", obj);

        addn("combat_exp", record, who);
        addn("shen", -bonus, who);
        addn("score", bonus, obj);

        remove_call_out("store");
        call_out("store", 1, ob);
        return 1;
}

// duty 4  teach skills
string ask_skills()
{
        object ling, me = this_player();
        int amount;

        if( is_fighting() )
                return RANK_D->query_rude(me) + "瞎了眼没见我正忙着？！";

        if( query_temp("bangs/fam", me) != query("fam") )
                return RANK_D->query_rude(me) + "莫非是想打听我帮的秘密吧。";

        if( !(ling = present("bang ling", me)) )
                return RANK_D->query_rude(me) + "竟连自己的帮令都管不住！";

        if( query("owner", ling) != query("id", me) )
                return RANK_D->query_rude(me) + "竟连自己的帮令都管不住！";

        if( (amount=query("score", ling))<10 )
                return RANK_D->query_rude(me) + "再加把劲，帮主才会指点你一下！";

        if( amount > 100 ) {
                set_temp("bangs/skills_asked", 100, me);
                addn("score", -100, ling);
        } else {
                set_temp("bangs/skills_asked", amount, me);
                delete("score", ling);
        }
        tell_object(me, "请键入：武功的英文名字。\n");
        return "好吧。";
}

int do_xue(string arg)
{
        object me = this_player();
        string *sname;
        int i, amount, level, mylvl;

        if( !(amount=query_temp("bangs/skills_asked", me))){
                write("你还没征求帮主同意呢。\n");
                return 1;
        }

        if( is_fighting() ) {
                say(name() + "大怒道：" + RANK_D->query_rude(me) + "瞎了眼没见我正忙着？！");
                return 1;
        }

        if( !arg ) {
                sname = keys(query_skills());
                write("\n" + name() + "所学过的技能：\n\n");
                for(i = 0; i < sizeof(sname); i++)
                        write(to_chinese(sname[i]) + " (" + sname[i] + ")" + "\n");
                return 1;
        }

        if( (level = (int)query_skill(arg, 1)) < 1 ) {
                say(name() + "摇了摇头道：帮主没学过。\n");
                return 1;
        }

        mylvl = (int)me->query_skill(arg, 1);
        if( level < mylvl ) {
                say(name() + "大怒道：" + RANK_D->query_rude(me) + "居然超过老子了。\n");
                return 1;
        }

        if( mylvl > 80 ) {
                say(name() + "摇了摇头道：你得去门派中正式拜师才能继续提高" + to_chinese(arg) + "。\n");
                return 1;
        }

        if( query("jing", me)+10<query("max_jing", me)){
                write("你先歇会儿吧。\n");
                return 1;
        }

        set("jing", 10, me);
        me->improve_skill(arg,amount*query("int", me)/3);
        delete_temp("bangs/skills_asked", me);

        message_vision("$N向$n请教有关「" + to_chinese(arg) + "」的疑问。\n", me, this_object());
        tell_object(me, "你听了帮主的指导，对「" + to_chinese(arg) + "」似乎有些心得。\n");
        return 1;
}

void store(object ob)
{
        if(ob) destruct(ob);
}

private is_victim(object ob, string arg)
{
        string fam;

        if( !stringp(fam=query("title", ob)))return 0;
        if( fam == arg ) return 0;

        return 1;
}
*/
