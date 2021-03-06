BEEGFS_FEATURE_DETECTION := $(shell $(dir $(lastword $(MAKEFILE_LIST)))/../build/feature-detect.sh)
ifneq ($(lastword $(BEEGFS_FEATURE_DETECTION)),--~~success~~--)
   $(error feature detection reported an error)
else
   BEEGFS_FEATURE_DETECTION := $(filter-out --~~success~~--,$(BEEGFS_FEATURE_DETECTION))
endif

# ccflags-y was introduced in 2.6.24, earlier kernels use EXTRA_CFLAGS for the same purpose
ifeq ($(origin ccflags-y),file)
ccflags-y += $(BEEGFS_FEATURE_DETECTION)
else
# the client makefile sets this already
override EXTRA_CFLAGS += $(BEEGFS_FEATURE_DETECTION)
endif

obj-m	+= ${TARGET}.o

SOURCES := \
   fault-inject/fault-inject.c \
   os/atomic64.c \
   os/OsCompat.c \
   os/OsDeps.c \
   net/message/NetMessageFactory.c \
   net/filesystem/FhgfsOpsCommKit.c \
   net/filesystem/FhgfsOpsRemoting.c \
   net/filesystem/FhgfsOpsCommKitVec.c \
   common/system/System.c \
   common/net/sock/Socket.c \
   common/net/sock/NicAddress.c \
   common/net/sock/NetworkInterfaceCard.c \
   common/net/sock/RDMASocket.c \
   common/net/sock/ibv/IBVSocket.c \
   common/net/sock/ibv/IBVBuffer.c \
   common/net/sock/ibv/No_IBVSocket.c \
   common/net/sock/StandardSocket.c \
   common/net/message/control/PeerInfoMsg.c \
   common/net/message/helperd/GetHostByNameMsg.c \
   common/net/message/helperd/LogMsg.c \
   common/net/message/helperd/GetHostByNameRespMsg.c \
   common/net/message/SimpleIntMsg.c \
   common/net/message/NetMessage.c \
   common/net/message/session/locking/FLockEntryMsg.c \
   common/net/message/session/locking/FLockAppendMsg.c \
   common/net/message/session/locking/LockGrantedMsgEx.c \
   common/net/message/session/locking/FLockRangeMsg.c \
   common/net/message/session/GetFileVersionRespMsg.c \
   common/net/message/session/rw/ReadLocalFileV2Msg.c \
   common/net/message/session/rw/WriteLocalFileMsg.c \
   common/net/message/session/FSyncLocalFileMsg.c \
   common/net/message/session/GetFileVersionMsg.c \
   common/net/message/session/opening/OpenFileMsg.c \
   common/net/message/session/opening/OpenFileRespMsg.c \
   common/net/message/session/opening/CloseFileMsg.c \
   common/net/message/session/BumpFileVersion.c \
   common/net/message/SimpleInt64Msg.c \
   common/net/message/SimpleUInt16Msg.c \
   common/net/message/SimpleStringMsg.c \
   common/net/message/SimpleIntStringMsg.c \
   common/net/message/nodes/RegisterNodeMsg.c \
   common/net/message/nodes/RegisterNodeRespMsg.c \
   common/net/message/nodes/HeartbeatRequestMsgEx.c \
   common/net/message/nodes/MapTargetsMsgEx.c \
   common/net/message/nodes/GetTargetMappingsRespMsg.c \
   common/net/message/nodes/HeartbeatMsgEx.c \
   common/net/message/nodes/RemoveNodeMsgEx.c \
   common/net/message/nodes/GetStatesAndBuddyGroupsRespMsg.c \
   common/net/message/nodes/RefreshTargetStatesMsgEx.c \
   common/net/message/nodes/GetNodesRespMsg.c \
   common/net/message/nodes/SetMirrorBuddyGroupMsgEx.c \
   common/net/message/SimpleMsg.c \
   common/net/message/storage/moving/RenameMsg.c \
   common/net/message/storage/StatStoragePathRespMsg.c \
   common/net/message/storage/creating/HardlinkMsg.c \
   common/net/message/storage/creating/MkFileMsg.c \
   common/net/message/storage/creating/MkDirMsg.c \
   common/net/message/storage/creating/UnlinkFileMsg.c \
   common/net/message/storage/creating/MkDirRespMsg.c \
   common/net/message/storage/creating/RmDirMsg.c \
   common/net/message/storage/creating/MkFileRespMsg.c \
   common/net/message/storage/attribs/StatRespMsg.c \
   common/net/message/storage/attribs/ListXAttrRespMsg.c \
   common/net/message/storage/attribs/SetAttrMsg.c \
   common/net/message/storage/attribs/ListXAttrMsg.c \
   common/net/message/storage/attribs/RefreshEntryInfoMsg.c \
   common/net/message/storage/attribs/StatMsg.c \
   common/net/message/storage/attribs/GetXAttrRespMsg.c \
   common/net/message/storage/attribs/GetXAttrMsg.c \
   common/net/message/storage/attribs/RemoveXAttrMsg.c \
   common/net/message/storage/attribs/SetXAttrMsg.c \
   common/net/message/storage/lookup/LookupIntentRespMsg.c \
   common/net/message/storage/lookup/LookupIntentMsg.c \
   common/net/message/storage/TruncFileMsg.c \
   common/net/message/storage/listing/ListDirFromOffsetRespMsg.c \
   common/net/message/storage/listing/ListDirFromOffsetMsg.c \
   common/threading/Thread.c \
   common/toolkit/Serialization.c \
   common/toolkit/MessagingTk.c \
   common/toolkit/HashTk.c \
   common/toolkit/ackstore/WaitAckMap.c \
   common/toolkit/ackstore/AcknowledgmentStore.c \
   common/toolkit/ackstore/AckStoreMap.c \
   common/toolkit/Random.c \
   common/toolkit/tree/IntMap.c \
   common/toolkit/tree/StrCpyMap.c \
   common/toolkit/tree/PointerRBTree.c \
   common/toolkit/NodesTk.c \
   common/toolkit/SocketTk.c \
   common/toolkit/MetadataTk.c \
   common/toolkit/TimeAbs.c \
   common/toolkit/StringTk.c \
   common/toolkit/ListTk.c \
   common/Types.c \
   common/nodes/Node.c \
   common/nodes/TargetMapper.c \
   common/nodes/MirrorBuddyGroup.c \
   common/nodes/NumNodeID.c \
   common/nodes/TargetStateStore.c \
   common/nodes/NodeTree.c \
   common/nodes/MirrorBuddyGroupMapper.c \
   common/nodes/NodeConnPool.c \
   common/storage/StorageErrors.c \
   common/storage/StatData.c \
   common/storage/striping/BuddyMirrorPattern.c \
   common/storage/striping/SimplePattern.c \
   common/storage/striping/StripePattern.c \
   common/storage/striping/Raid10Pattern.c \
   common/storage/striping/Raid0Pattern.c \
   common/storage/PathInfo.c \
   common/storage/EntryInfo.c \
   common/storage/StoragePoolId.c \
   common/storage/FileEvent.c \
   program/Main.c \
   toolkit/FhgfsChunkPageVec.c \
   toolkit/StatFsCache.c \
   toolkit/NoAllocBufferStore.c \
   toolkit/InodeRefStore.c \
   toolkit/ExternalHelperd.c \
   toolkit/BitStore.c \
   components/DatagramListener.c \
   components/InternodeSyncer.c \
   components/Flusher.c \
   components/worker/RWPagesWork.c \
   components/AckManager.c \
   nodes/NodeStoreEx.c \
   filesystem/ProcFs.c \
   filesystem/FhgfsOpsPages.c \
   filesystem/FhgfsOpsFile.c \
   filesystem/FhgfsOpsInode.c \
   filesystem/FhgfsOpsFileNative.c \
   filesystem/FhgfsInode.c \
   filesystem/helper/IoctlHelper.c \
   filesystem/FsFileInfo.c \
   filesystem/ProcFsHelper.c \
   filesystem/FhgfsOpsSuper.c \
   filesystem/FhgfsOps_versions.c \
   filesystem/FhgfsXAttrHandlers.c \
   filesystem/FhgfsOpsDir.c \
   filesystem/FhgfsOpsIoctl.c \
   filesystem/FhgfsOpsExport.c \
   filesystem/FhgfsOpsHelper.c \
   app/App.c \
   app/log/Logger.c \
   app/config/MountConfig.c \
   app/config/Config.c

${TARGET}-y	:= $(patsubst %.c,%.o,$(SOURCES))

ifneq ($(OFED_INCLUDE_PATH),)

ifeq ($(shell [ -f $(OFED_INCLUDE_PATH)/linux/compat-2.6.h ] && echo 1),1)
$(src)/common/net/sock/ibv/IBVSocket.o: CC+=-include $(OFED_INCLUDE_PATH)/linux/compat-2.6.h
$(src)/common/net/sock/ibv/IBVBuffer.o: CC+=-include $(OFED_INCLUDE_PATH)/linux/compat-2.6.h
endif

$(src)/common/net/sock/ibv/IBVSocket.o: CC+=-I$(OFED_INCLUDE_PATH) -I$(OFED_INCLUDE_PATH)/uapi
$(src)/common/net/sock/ibv/IBVBuffer.o: CC+=-I$(OFED_INCLUDE_PATH) -I$(OFED_INCLUDE_PATH)/uapi
endif
