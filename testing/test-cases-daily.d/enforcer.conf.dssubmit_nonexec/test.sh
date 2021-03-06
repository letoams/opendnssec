#!/usr/bin/env bash
#
#TEST: Test to see that a  non executable DSSUB command is dealt with as expected

ENFORCER_WAIT=90	# Seconds we wait for enforcer to run
ENFORCER_COUNT=2	# How many log lines we expect to see

cp dssub.pl "$INSTALL_ROOT/var/opendnssec/enforcer/" &&

if [ -n "$HAVE_MYSQL" ]; then
        ods_setup_conf conf.xml conf-mysql.xml
fi &&

ods_reset_env &&

##################  SETUP ###########################
# Start enforcer (Zone already exists and we let it generate keys itself)
ods_start_enforcer &&


# Check that we are trying to use the correct (non-exec) command:
#syslog_grep " ods-enforcerd: .*Using command: $INSTALL_ROOT/var/opendnssec/enforcer/dssub.pl to submit DS records" &&

# Check that we have 2 keys
log_this ods-enforcer-key-list1 ods-enforcer key list -a &&
log_grep ods-enforcer-key-list1 stdout 'ods[[:space:]]*KSK[[:space:]]*publish' &&
log_grep ods-enforcer-key-list1 stdout 'ods[[:space:]]*ZSK[[:space:]]*ready' &&

# Grab the KEYTAG of the KSK
log_this ods-enforcer-keytag ods-enforcer key list --verbose --all &&
KSK_KEYTAG=`log_grep -o ods-enforcer-keytag stdout "ods[[:space:]]*KSK[[:space:]]*publish" | awk '{print $10}'` &&

## Jump forward a couple of hours so the KSK will be ready
##################  STEP 1: Time = 4hrs ###########################
ods_enforcer_leap_to 14400 &&


# We should be ready for a ds-submit and ds-seen on ods
syslog_grep "ods-enforcerd: .*please submit DS with keytag $KSK_KEYTAG for zone ods" &&

# Check syslog for the command failing
syslog_grep "ods-enforcerd: .*File $INSTALL_ROOT/var/opendnssec/enforcer/dssub.pl is not executable" &&

# Check that no dssub.out file exists
echo "Testing dssub.out doesn't exist" &&
! test -f "$INSTALL_ROOT/var/opendnssec/enforcer/dssub.out" &&

# Clean up
echo "Cleaning up files" &&
rm "$INSTALL_ROOT/var/opendnssec/enforcer/dssub.pl" &&


ods_stop_enforcer &&
return 0

# Something went wrong, make sure clean up tmp if nothing else
rm "$INSTALL_ROOT/var/opendnssec/enforcer/*" &&

echo
echo "************ERROR******************"
echo
ods_kill
return 1

