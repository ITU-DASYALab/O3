# -*- coding: utf-8 -*-
import ObjectCubePython, os, glob, sys, time, pdb
from ObjectCubePython import *
'''
print '---------- Object 1 ----------'
obj1 = Object("/home/snorri/Desktop/TestPlugin/CheckBackTomorrow.txt")
obj1.create()

print '---------- Object 1 ----------'
obj1.thumbnail = 'ThumbnailObj1'
obj1.fileType = 'TypeObj1'
obj1.update()
obj1Id = obj1.id

obj1Test = Object()
obj1Test = obj1Test.fetch(obj1Id)


print 'Object1 name = ' + obj1Test.name
print 'Object1 thumbnail = ' + obj1Test.thumbnail
print 'Object1 fileType = ' + obj1Test.fileType
'''
obj2 = Object("/home/snorri/Desktop/TestPlugin/IMG_0049.JPG")
obj2.create()
'''
print '---------- Object 2 ----------'
obj2.thumbnail = 'ThumbnailObj2'
obj2.fileType = 'TypeObj2'
obj2.update()
obj2Id = obj2.id

obj2Test = Object()
obj2Test = obj2Test.fetch(obj2Id)

print 'Object2 name = ' + obj2Test.name
print 'Object2 thumbnail = ' + obj2Test.thumbnail
print 'Object2 fileType = ' + obj2Test.fileType

obj3 = Object("/home/snorri/Desktop/TestPlugin/RL.mp4")
obj3.create()

print '---------- Object 3 ----------'
obj3.thumbnail = 'ThumbnailObj3'
obj3.fileType = 'TypeObj3'
obj3.update()
obj3Id = obj3.id

obj3Test = Object()
obj3Test = obj3Test.fetch(obj3Id)

print 'Object3 name = ' + obj3Test.name
print 'Object3 thumbnail = ' + obj3Test.thumbnail
print 'Object3 fileType = ' + obj3Test.fileType
'''