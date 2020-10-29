// This program is a part of NT MudLIB

mixed valid_database(object ob, string action, mixed *info)
{
        if( !objectp(ob) || (geteuid(ob) != ROOT_UID) )
                return 0;

        else
        {
                if( action == "connect" ) {
                        /*
                         * 这里演示的多站点数据库互动
                         * 协作的返回密码写法，单站点
                         * 简单返回密码即可（by Find）
                         */
         
                        switch (info[1])
                        {
                             case "127.0.0.1":              // 其它站点的地址
                                        return "xkx200303";      // 这个站点的密码
                                case "localhost":
                                        return "xkx200303";      // 本地站点的密码
                               default:
                                  if(info[0]=="/adm/etc/userdb.db") 
                                  return 1;
                                  else
                                        return 0;
                        }

                }
                else
                        return 1;
        }
}
