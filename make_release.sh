#! /bin/sh

version_number=$1

last_release=$(git tag | sort -rV | head -n 1 | sed 's|^release-||')
echo "The last release was ${last_release}"

if [ -z "$version_number" ]; then
    echo "Please use a semver number as argument, eg sh make_release.sh '2.0.1'" >&2
    exit 1
fi

echo "$version_number" > version
git commit -am "releasing v${version_number}"
git tag -a "release-${version_number}" -m "release ${version_number}"

read -p "Push tag (y/n)? " choice
case "$choice" in 
    y|Y)
        git push --tags
        ;;
    n|N) 
        ;;
    *) 
        echo "invalid"
        ;;
esac

