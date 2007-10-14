EnsureSConsVersion(0, 96)

import os
import configure

root = os.environ.get('RSFROOT',os.getcwd())

bindir = os.path.join(root,'bin')
libdir = os.path.join(root,'lib')
incdir = os.path.join(root,'include')
docdir = os.path.join(root,'doc')

env = Environment()

##########################################################################
# CONFIGURATION
##########################################################################

opts = Options('config.py')
configure.options(opts)
opts.Add('RSFROOT','RSF installation root',root)
opts.Update(env)

if not os.path.isfile('config.py'):
    conf = Configure(env,custom_tests={'CheckAll':configure.check_all})
    conf.CheckAll()
    env = conf.Finish()
    
Help(opts.GenerateHelpText(env))
opts.Save('config.py',env)

config = env.Command('config.py','configure.py','')
env.Precious(config)

env.InstallAs(os.path.join(libdir,'rsfconfig.py'),'config.py')
env.InstallAs(os.path.join(libdir,'rsfconf.py'),'configure.py')
Clean(config,['#/config.log','#/.sconf_temp','configure.pyc'])
env.Alias('config',config)

##########################################################################
# PYTHON BUILD
##########################################################################

user = filter(lambda x: x[0] != '.' and x != 'nobody', os.listdir('user'))
env['USERS']=user

Export('env')
SConscript(dirs='python',name='SConstruct')

env.Append(BUILDERS={'Include':configure.Header,'Place':configure.Place},
           SCANNERS=[configure.Include])

##########################################################################
# FILT BUILD
##########################################################################
Export('env')
dirs = ('lib','main','proc','imag')

Default('build/include')
subdirs = map(lambda x: os.path.join('filt',x), dirs) + \
          map(lambda x: os.path.join('user',x), user)
for dir in subdirs:
    build = os.path.join('build',dir)
    BuildDir(build,dir)
    SConscript(dirs=build,name='SConstruct')
    Default(build)

##########################################################################
# PLOT BUILD
##########################################################################

oldpath = env.get('LIBPATH',[])
oldlibs = env.get('LIBS',[])

Export('env')
pdirs = ('lib','main','test','su')

Default('build/include')
for dir in map(lambda x: os.path.join('plot',x), pdirs):
    build = os.path.join('build',dir)
    BuildDir(build,dir)
    SConscript(dirs=build,name='SConstruct')
    Default(build)

##########################################################################
# PENS BUILD
##########################################################################
Export('env')
pdirs = ('fonts','include','utilities','genlib','main')

Default('build/include')
for dir in map(lambda x: os.path.join('pens',x), pdirs):
    build = os.path.join('build',dir)
    BuildDir(build,dir)
    SConscript(dirs=build,name='SConstruct')
    Default(build)

##########################################################################
# INSTALLATION
##########################################################################

rsfuser = os.path.join(libdir,'rsfuser')
env.Install(rsfuser,'__init__.py')

env.Alias('install',[incdir,bindir,libdir,rsfuser,docdir])

# 	$Id$
